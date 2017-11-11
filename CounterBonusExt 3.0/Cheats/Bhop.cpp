#include "Bhop.h"

bool bBhopThreadStop = false;

bool isAir()
{
	int flags = Memory->Read<int>(Offsets->m_dwLocalPlayer + NetVars->m_fFlags) == 256;
	return flags == 256 || flags == 258 || flags == 260 || flags == 262;
}

void bhop()
{
	while (true)
	{
		while (!bBhopThreadStop)
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				//if (Memory->Read<BYTE> (Offsets->m_dwLocalPlayer + NetVars->m_fFlags) & FL_ONGROUND)
				if (!isAir())
				{
					Console->DebugMessage("on ground");
					// 0x04EE6194
					Memory->Write<DWORD>(Memory->GetClientBase() + Offsets->m_dwForceJump, 5);
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
					Memory->Write<DWORD>(Memory->GetClientBase() + Offsets->m_dwForceJump, 4);
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}