#include "Player.h"

#pragma warning( disable : 4172)

CPlayer* player = new CPlayer ();

CPlayer::CPlayer ()
{}

CPlayer::~CPlayer ()
{
	player = NULL;
}

void CPlayer::getPlayer (int i)
{
	player = Mem->ReadMem<DWORD> (Offsets->clientDll + Offsets->EntityList + (i * 0x10));
}

float* CPlayer::getPos ()
{
	float pos[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(player + Offsets->m_vecOrigin), &pos, sizeof (float) * 3, 0);
	return pos;
}

Vector CPlayer::getVecPos ()
{
	Vector pos;
	pos = Mem->ReadMem<Vector> (player + Offsets->m_vecOrigin);
	return pos;
}

float* CPlayer::getEyePos ()
{
	float eye[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(player + Offsets->m_vecViewOffset), &eye, sizeof (float) * 3, 0);
	eye[ 0 ] += getPos ()[ 0 ];
	eye[ 1 ] += getPos ()[ 1 ];
	eye[ 2 ] += getPos ()[ 2 ];
	return eye;
}

Vector CPlayer::getVelocity ()
{
	return Mem->ReadMem<Vector> (player + Offsets->m_vecVelocity);
}

int CPlayer::getHealth ()
{
	return Mem->ReadMem<int> (player + Offsets->m_iHealth);
}

int CPlayer::getTeam ()
{
	return Mem->ReadMem<int> (player + Offsets->m_iTeamNum);
}

int CPlayer::getFlags ()
{
	return Mem->ReadMem<int> (player + Offsets->m_fFlags);
}

int CPlayer::getGlowIndex ()
{
	return Mem->ReadMem<int> (player + Offsets->m_iGlowIndex);
}

int CPlayer::getClassID ()
{
	int vt = Mem->ReadMem<DWORD> (player + 0x8);
	int fn = Mem->ReadMem<DWORD> (vt + 2 * 0x4);
	int cls = Mem->ReadMem<DWORD> (fn + 0x1);
	int clsn = Mem->ReadMem<DWORD> (cls + 8);
	return Mem->ReadMem<int> (cls + 20);
}

bool CPlayer::getAlive ()
{
	return engine->alive (getHealth ());
}

bool CPlayer::isDead ()
{
	return Mem->ReadMem<bool> (player + Offsets->m_lifeState);
}

bool CPlayer::isDormant ()
{
	return Mem->ReadMem<bool> (player + Offsets->m_bDormant);
}

DWORD CPlayer::getClientClass ()
{
	int vt = Mem->ReadMem<DWORD> (player + 0x8);
	int fn = Mem->ReadMem<DWORD> (vt + 2 * 0x4);
	int cls = Mem->ReadMem<DWORD> (fn + 0x1);
	int clsn = Mem->ReadMem<DWORD> (cls + 8);
	return cls;
}

DWORD CPlayer::getBoneMatrix ()
{
	return Mem->ReadMem<DWORD> (player + Offsets->m_dwBoneMatrix);
}

void CPlayer::getBonePos (DWORD boneBase, int boneID, float * bonePos)
{
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(boneBase + 0x30 * boneID + 0x0C), &bonePos[ 0 ], sizeof (float), 0);
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(boneBase + 0x30 * boneID + 0x1C), &bonePos[ 1 ], sizeof (float), 0);
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(boneBase + 0x30 * boneID + 0x2C), &bonePos[ 2 ], sizeof (float), 0);
}

void CPlayer::vecGetBonePos (DWORD boneBase, int boneID, Vector &bonePos)
{
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(boneBase + 0x30 * boneID + 0x0C), &bonePos[ 0 ], sizeof (float), 0);
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(boneBase + 0x30 * boneID + 0x1C), &bonePos[ 1 ], sizeof (float), 0);
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(boneBase + 0x30 * boneID + 0x2C), &bonePos[ 2 ], sizeof (float), 0);
}

float* CPlayer::getHead ()
{
	float head[ 3 ];
	getBonePos (getBoneMatrix (), 6, head);
	return head;
}

float* CPlayer::getBone (int bone)
{
	float bone_pos[ 3 ];
	getBonePos (getBoneMatrix (), bone, bone_pos);
	return bone_pos;
}

Vector CPlayer::vecGetBone (int bone)
{
	Vector bone_pos;
	vecGetBonePos (getBoneMatrix (), bone, bone_pos);
	return bone_pos;
}