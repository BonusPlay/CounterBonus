#pragma once
#include "Cheats.hpp"

#include <cstdio>
#include <Windows.h>

#include "Config.hpp"
#include "Memory.hpp"

bool isAir()
{
	int flag = Memory->ReadMem<int>(Config->getLocalPlayer() + 0x100);
	std::cout << flag << std::endl;
	return flag == 256 || flag == 258 || flag == 260 || flag == 262;
}

void bhop()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !isAir())
		{
			Memory->WriteMem(Memory->clientDll + Config->getForceJump(), 5);
		}
		else if (GetAsyncKeyState(VK_SPACE) & 0x8000 && isAir())
		{
			Memory->WriteMem(Memory->clientDll + Config->getForceJump(), 4);
			Memory->WriteMem(Memory->clientDll + Config->getForceJump(), 5);
			Memory->WriteMem(Memory->clientDll + Config->getForceJump(), 4);
		}
		else
		{
			Memory->WriteMem(Memory->clientDll + Config->getForceJump(), 4);
		}
		Sleep(20);
	}
}