#include "Engine.h"

#pragma warning( disable : 4244)

#define M_PI 3.14159265358979323846f
#define M_RADPI 57.295779513082f

CEngine* engine = new CEngine ();
CCommandVar* commandVar = new CCommandVar ("");

CEngine::CEngine ()
{
	cout << XOR ("[Engine] Getting modules...") << endl;
	Offsets->clientDll = Mem->Module (XOR ("client.dll"));
	Offsets->engineDll = Mem->Module (XOR ("engine.dll"));
	Offsets->clientDllSize = Mem->ModuleSize (XOR ("client.dll"));
	Offsets->engineDllSize = Mem->ModuleSize (XOR ("engine.dll"));

	assert (Offsets->clientDll);
	assert (Offsets->engineDll);
	assert (Offsets->clientDllSize);
	assert (Offsets->engineDllSize);

	cout << XOR ("[Engine] Initialized modules:") << endl;
	cout << XOR ("> client.dll [at 0x") << Offsets->clientDll << XOR (" , size 0x") << Offsets->clientDllSize << XOR (" bytes") << endl;
	cout << XOR ("> engine.dll [at 0x") << Offsets->engineDll << XOR (" , size 0x") << Offsets->engineDllSize << XOR (" bytes") << endl;

	cout << XOR ("[Engine] Getting offsets...") << endl;
	FindLocalPlayer ();
	FindEntityList ();
	FindAttack ();
	FindJump ();
	FindCrosshairID ();
	FindGlowObject ();
	FindViewMatrix ();
	FindEnginePointer ();
	FindViewAngles ();

	assert (Offsets->LocalPlayer);
	assert (Offsets->EntityList);
	assert (Offsets->Attack);
	assert (Offsets->Jump);
	assert (Offsets->CrosshairID);
	assert (Offsets->GlowObject);
	assert (Offsets->ViewMatrix);
	assert (Offsets->ClientState);
	assert (Offsets->ViewAngles);

	cout << XOR ("[Engine] Initialized offsets:") << endl;
	cout << XOR ("> LocalPlayer : 0x") << Offsets->LocalPlayer << endl;
	cout << XOR ("> EntityList  : 0x") << Offsets->EntityList << endl;
	cout << XOR ("> Attack      : 0x") << Offsets->Attack << endl;
	cout << XOR ("> Jump        : 0x") << Offsets->Jump << endl;
	cout << XOR ("> CrosshairID : 0x") << Offsets->CrosshairID << endl;
	cout << XOR ("> GlowObject  : 0x") << Offsets->GlowObject << endl;
	cout << XOR ("> ViewMatrix  : 0x") << Offsets->ViewMatrix << endl;
	cout << XOR ("> ClientState : 0x") << Offsets->ClientState << endl;
	cout << XOR ("> ViewAngles  : 0x") << Offsets->ViewAngles << endl;
}

CEngine::~CEngine ()
{}

void CEngine::attack ()
{
	Mem->WriteMem<int> (Offsets->clientDll + Offsets->Attack, 5);
	Sleep (20);
	Mem->WriteMem<int> (Offsets->clientDll + Offsets->Attack, 4);
	Sleep (15);
}

bool CEngine::alive (int hp)
{
	if (hp < 2)
		return false;
	else
		return true;
}

void CEngine::MakeVector (float *pfIn, float *pfOut)
{
	float pitch;
	float yaw;
	float tmp;

	pitch = (float)(pfIn[ 0 ] * M_PI / 180);
	yaw = (float)(pfIn[ 1 ] * M_PI / 180);
	tmp = (float)cos (pitch);

	pfOut[ 0 ] = (float)(-tmp * -cos (yaw));
	pfOut[ 1 ] = (float)(sin (yaw)*tmp);
	pfOut[ 2 ] = (float)-sin (pitch);
}

void CEngine::CalcAngle (float *src, float *dst, float *angles)
{
	double delta[ 3 ] = { (src[ 0 ] - dst[ 0 ]), (src[ 1 ] - dst[ 1 ]), (src[ 2 ] - dst[ 2 ]) };
	double hyp = sqrt (delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ]);

	angles[ 0 ] = (float)(atan (delta[ 2 ] / hyp) * M_RADPI);
	angles[ 1 ] = (float)(atan (delta[ 1 ] / delta[ 0 ]) * M_RADPI);
	angles[ 2 ] = 0.0f;

	if (delta[ 0 ] >= 0.0) { angles[ 1 ] += 180.0f; }
}

void CEngine::calcang (float *src, float *dst, float *punch, float *angles)
{
	double delta[ 3 ] = { (src[ 0 ] - dst[ 0 ]), (src[ 1 ] - dst[ 1 ]), (src[ 2 ] - (dst[ 2 ] - 61)) };
	double hyp = sqrt (delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ]);
	angles[ 0 ] = (float)(atanf (delta[ 2 ] / hyp) * 57.295779513082f - (punch[ 0 ] * 2.0f));
	angles[ 1 ] = (float)(atanf (delta[ 1 ] / delta[ 0 ]) * 57.295779513082f - (punch[ 1 ] * 2.0f));
	angles[ 2 ] = 0.0f;

	if (delta[ 0 ] >= 0.0)
	{
		angles[ 1 ] += 180.0f;
	}
}

float CEngine::GetFOV (float *angle, float *src, float *dst)
{
	float ang[ 3 ], aim[ 3 ];
	float fov;

	CalcAngle (src, dst, ang);
	MakeVector (angle, aim);
	MakeVector (ang, ang);

	float mag_s = sqrt ((aim[ 0 ] * aim[ 0 ]) + (aim[ 1 ] * aim[ 1 ]) + (aim[ 2 ] * aim[ 2 ]));
	float mag_d = sqrt ((aim[ 0 ] * aim[ 0 ]) + (aim[ 1 ] * aim[ 1 ]) + (aim[ 2 ] * aim[ 2 ]));

	float u_dot_v = aim[ 0 ] * ang[ 0 ] + aim[ 1 ] * ang[ 1 ] + aim[ 2 ] * ang[ 2 ];

	fov = acos (u_dot_v / (mag_s*mag_d)) * (180.0f / M_PI);

	return fov;
}

void CEngine::clampAngles (float* angles)
{
	if (angles[ 0 ] > 180) angles[ 0 ] -= 360;
	if (angles[ 1 ] > 180) angles[ 1 ] -= 360;
	if (angles[ 0 ] < -180) angles[ 0 ] += 360;
	if (angles[ 1 ] < -180) angles[ 1 ] += 360;

	while (angles[ 0 ] > 89.0f && angles[ 0 ] <= 180.0f) angles[ 0 ] = 89.0f;
}

typedef struct
{
	float flMatrix[ 4 ][ 4 ];
}WorldToScreenMatrix_t;

bool CEngine::WorldToScreen (float * from, float * to, RECT rc)
{
	WorldToScreenMatrix_t WorldToScreenMatrix;
	WorldToScreenMatrix = Mem->ReadMem<WorldToScreenMatrix_t> (Offsets->clientDll + Offsets->ViewMatrix);
	float w = 0.0f;

	to[ 0 ] = WorldToScreenMatrix.flMatrix[ 0 ][ 0 ] * from[ 0 ] + WorldToScreenMatrix.flMatrix[ 0 ][ 1 ] * from[ 1 ] + WorldToScreenMatrix.flMatrix[ 0 ][ 2 ] * from[ 2 ] + WorldToScreenMatrix.flMatrix[ 0 ][ 3 ];
	to[ 1 ] = WorldToScreenMatrix.flMatrix[ 1 ][ 0 ] * from[ 0 ] + WorldToScreenMatrix.flMatrix[ 1 ][ 1 ] * from[ 1 ] + WorldToScreenMatrix.flMatrix[ 1 ][ 2 ] * from[ 2 ] + WorldToScreenMatrix.flMatrix[ 1 ][ 3 ];
	w = WorldToScreenMatrix.flMatrix[ 3 ][ 0 ] * from[ 0 ] + WorldToScreenMatrix.flMatrix[ 3 ][ 1 ] * from[ 1 ] + WorldToScreenMatrix.flMatrix[ 3 ][ 2 ] * from[ 2 ] + WorldToScreenMatrix.flMatrix[ 3 ][ 3 ];

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;
	to[ 0 ] *= invw;
	to[ 1 ] *= invw;

	int width = (int)(rc.right - rc.left);
	int height = (int)(rc.bottom - rc.top);

	float x = width / 2;
	float y = height / 2;

	x += 0.5 * to[ 0 ] * width + 0.5;
	y -= 0.5 * to[ 1 ] * height + 0.5;

	to[ 0 ] = x + rc.left;
	to[ 1 ] = y + rc.top;

	return true;
}

void CEngine::smoothAngles (float* angles, float* out)
{
	float qCurrentView[ 3 ] = { angles[ 0 ], angles[ 1 ], angles[ 2 ] };
	float qDelta[ 3 ] = { out[ 0 ] - qCurrentView[ 0 ], out[ 1 ] - qCurrentView[ 1 ], out[ 2 ] - qCurrentView[ 2 ] };
	clampAngles (qDelta);
	out[ 0 ] = qCurrentView[ 0 ] + qDelta[ 0 ] / Settings->aimSmooth;
	out[ 1 ] = qCurrentView[ 1 ] + qDelta[ 1 ] / Settings->aimSmooth;
	out[ 2 ] = qCurrentView[ 2 ] + qDelta[ 2 ] / Settings->aimSmooth;
}

void CEngine::FindLocalPlayer ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x00", XOR ("xxx????xx????xxxxx?"));
	DWORD p1 = Mem->ReadMem<DWORD> (start + 3);
	BYTE p2 = Mem->ReadMem<BYTE> (start + 18);
	Offsets->LocalPlayer = (p1 + p2) - Offsets->clientDll;
}

void CEngine::FindEntityList ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\x05\x00\x00\x00\x00\xC1\xE9\x00\x39\x48\x04", XOR ("x????xx?xxx"));
	DWORD p1 = Mem->ReadMem<DWORD> (start + 1);
	BYTE p2 = Mem->ReadMem<BYTE> (start + 7);
	Offsets->EntityList = (p1 + p2) - Offsets->clientDll;
}

void CEngine::FindAttack ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x04\xA8\x04\xBF", XOR ("xx????xx????xxxxxxxxxxx"));
	DWORD offset = Mem->ReadMem<DWORD> (start + 2);
	Offsets->Attack = offset - Offsets->clientDll;
}

void CEngine::FindJump ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x08\xA8\x08\xBF", XOR ("xx????xx????xxxxxxxxxxx"));
	DWORD offset = Mem->ReadMem<DWORD> (start + 2);
	Offsets->Jump = offset - Offsets->clientDll;
}

void CEngine::FindCrosshairID ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\x56\x57\x8B\xF9\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x81\xF9\x00\x00\x00\x00\x75\x07\xA1\x00\x00\x00\x00\xEB\x07", XOR ("xxxxxx????????xx????xx????xxx????xx"));
	DWORD offset = Mem->ReadMem<DWORD> (start + 6);
	Offsets->CrosshairID = offset;
}

void CEngine::FindGlowObject ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\xA1\x00\x00\x00\x00\xA8\x01\x75\x00\x0F\x57\xC0\xC7\x05", XOR ("x????xxx?xxxxx"));
	Offsets->GlowObject = Mem->ReadMem<DWORD> (start + 0x58) - Offsets->clientDll;
}

void CEngine::FindViewMatrix ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->clientDll, Offsets->clientDllSize, (PBYTE)"\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\xA1\x00\x00\x00\x00\x81\xEC\x98\x03\x00\x00", XOR ("xxxxxxxxxxxxxxxxxxxxxxx????xxxxxx"));
	start = Mem->ReadMem<DWORD> (start + 0x4EE);
	Offsets->ViewMatrix = (start + 0x80) - Offsets->clientDll;
}

void CEngine::FindEnginePointer ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->engineDll, Offsets->engineDllSize, (PBYTE)"\xF3\x0F\x5C\xC1\xF3\x0F\x10\x15\x00\x00\x00\x00\x0F\x2F\xD0\x76\x04\xF3\x0F\x58\xC1\xA1\x00\x00\x00\x00\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04", XOR ("xxxxxxxx????xxxxxxxxxx????xxxx????xxx"));
	Offsets->ClientState = Mem->ReadMem<DWORD> (start + 22) - Offsets->engineDll;
}

void CEngine::FindViewAngles ()
{
	DWORD start;
	start = Mem->FindSignature (Offsets->engineDll, Offsets->engineDllSize, (PBYTE)"\xF3\x0F\x5C\xC1\xF3\x0F\x10\x15\x00\x00\x00\x00\x0F\x2F\xD0\x76\x04\xF3\x0F\x58\xC1\xA1\x00\x00\x00\x00\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04", XOR ("xxxxxxxx????xxxxxxxxxx????xxxx????xxx"));
	Offsets->ViewAngles = Mem->ReadMem<DWORD> (start + 30);
}

unsigned char CCommandVar::table[] =
"\xEE\xA4\xBF\xA8\x73\x10\x8E\x0B\xD5\xD6\x39\x97\xF8\xFC\x1A\
\xC6\x0D\x69\x66\x19\x2B\x2A\xE3\x6B\xD2\xFB\x56\x42\x53\xC1\
\x7E\x6C\x83\x03\x40\xBA\xC0\x51\x25\x9E\x27\xF4\x0E\xFE\x4B\
\x1E\x02\x58\xAC\xB0\xFF\x45\x00\x2D\x74\x8B\x17\x41\xB7\x94\
\x21\x2E\xCB\x14\x8F\xCD\x3C\xC5\x76\x09\xAB\x33\xE9\x87\xDC\
\x31\x47\xB8\x52\x6D\x24\xA1\xA9\x96\x3F\x60\xAD\x7D\x71\x43\
\xE0\x4E\xE8\xD7\x23\xDB\x4F\xB5\x29\xE5\x95\x99\x6F\xD9\x15\
\x48\x78\xA3\x85\x28\x7A\x8C\xD0\xE7\xD3\xC8\xA0\xB6\x68\x6E\
\xB2\xED\x0F\x65\x1B\x32\x18\xBD\xB1\x82\xBB\x5C\xFD\x88\x64\
\xD4\x13\xAE\x46\x16\xAA\xCE\xA2\x4A\xF7\x05\x2F\x20\xB3\x75\
\x84\xC3\x7C\x7B\xF5\x80\xEC\xDF\x0C\x54\x36\xDA\x92\xE4\x9D\
\x5E\x6A\x1F\x11\x1D\xC2\x22\x38\x86\xEF\xF6\xF1\xD8\x7F\x62\
\x07\xCC\x9A\x98\xD1\xBC\x30\x3D\x57\x61\xE1\x55\x5A\xA7\x9B\
\x70\x91\x72\x8D\x5D\xFA\x04\xC9\x9C\x26\x59\xE2\xC4\x01\xEB\
\x2C\xB4\x9F\x79\x77\xA6\xBE\x90\x0A\x5B\x4C\xE6\xDD\x50\xCF\
\x37\x3A\x35\xAF\x08\x06\x34\x44\xF2\x12\xDE\x67\xF9\x93\x81\
\x8A\xF3\x1C\xB9\x3E\x3B\xF0\xCA\xEA\x63\x4D\x49\xC7\x89\x5F\xA5";

uint32_t CCommandVar::toHash (char* str)
{
	uint8_t ebx = 0;
	uint8_t edi = 0;
	uint8_t eax = 0;
	uint32_t r;

	if (str && strlen (str) > 0)
	{
		eax = toupper (str[ 0 ]);

		uint32_t i = 1;
		while (true)
		{
			eax ^= ebx;
			edi = table[ eax ];
			eax = toupper (str[ i ]);
			if (!eax)
				break;

			eax ^= edi;
			ebx = table[ eax ];
			eax = toupper (str[ i + 1 ]);
			if (!eax)
				break;

			i += 2;
		}
	}

	r = edi;
	r <<= 8;
	r |= ebx;

	return r;
}

void* CCommandVar::Find (char* str)
{
	uint32_t hash = CCommandVar::toHash (str);
	uint32_t entry = hash & 0xFF;
	uint32_t hashMapEntry;

	if (m_pICVar)
	{
		auto shortCuts = DEREF (uint32_t, m_pICVar, 52);
		hashMapEntry = DEREF (uint32_t, shortCuts, entry * 4);

		while (hashMapEntry)
		{
			auto hashMapEntryHash = DEREF (uint32_t, hashMapEntry, 0);
			if (hashMapEntryHash == hash)
			{
				void* pConVar = DEREF (void*, hashMapEntry, 4);
				char* pConVarName = DEREF (char*, pConVar, 12);
				if (!stricmp (pConVarName, str))
					return pConVar;
			}
			hashMapEntry = DEREF (uint32_t, hashMapEntry, 12);
		}
	}

	return 0;
}