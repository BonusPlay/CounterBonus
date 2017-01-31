#include "Bhop.h"

CBhop::CBhop ()
{
	Console->SuccessMessage ("> Bhop thread started!");
}

CBhop::~CBhop ()
{
	Console->SuccessMessage ("> Bhop thread shut down!");
}

void CBhop::Start ()
{
	while (!bBhopThreadTerminate)
	{
		while (!bBhopThreadStop)
		{
			if (GetAsyncKeyState (VK_SPACE) & 0x8000)
			{
				//if (Memory->Read<BYTE> (Offsets->m_dwLocalPlayer + NetVars->m_fFlags) & FL_ONGROUND)
				if (!isAir ())
				{
					// 0x04EE6194
					Memory->Write<DWORD> (Memory->GetClientBase () + Offsets->m_dwForceJump, 5);
					std::this_thread::sleep_for (std::chrono::milliseconds (10));
					Memory->Write<DWORD> (Memory->GetClientBase () + Offsets->m_dwForceJump, 4);
				}
			}

			std::this_thread::sleep_for (std::chrono::milliseconds (10));
		}
		std::this_thread::sleep_for (std::chrono::milliseconds (10));
	}
}

bool CBhop::isAir ()
{
	int flags = Memory->Read<int> (Offsets->m_dwLocalPlayer + NetVars->m_fFlags) == 256;
	return flags == 256 || flags == 258 || flags == 260 || flags == 262;
}