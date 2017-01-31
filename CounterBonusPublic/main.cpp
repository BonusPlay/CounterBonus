#include <Windows.h>
#include <iostream>
#include <string>

#include "Memory.h"

DWORD clientDll;
DWORD clientDllSize;

DWORD localPlayer;
DWORD entityList;
DWORD forceJump;

DWORD bDormant = 0xE9;
DWORD bSpotted = 0x939;

void updateEntityList ();
void updateLocalPlayer ();
void updateForceJump ();
void radar ();
void bhop ();
bool isAir ();
void log (std::string);

int main (int argc, char * argv[])
{
	log ("CounterBonusPublic v. 1.2");
	Mem->Process ("csgo.exe");
	clientDll = Mem->Module ("client.dll");
	clientDllSize = Mem->ModuleSize ("client.dll");
	//entityList = 0x04A57EA4;
	//localPlayer = 0x00A3A43C;
	//forceJump = 0x04EED318;
	updateEntityList ();
	updateLocalPlayer ();
	updateForceJump ();
	
	log ("client.dll hooked!");
	std::cout << "client.dll		: 0x" << std::hex << std::uppercase << clientDll << std::endl;
	std::cout << "client.dll size	: 0x" << std::hex << std::uppercase << clientDllSize << std::endl;
	std::cout << "EntityList		: 0x" << std::hex << std::uppercase << entityList << std::endl;
	std::cout << "LocalPlayer       : 0x" << std::hex << std::uppercase << localPlayer << std::endl;
	std::cout << "ForceJump         : 0x" << std::hex << std::uppercase << forceJump << std::endl;

	while (true)
	{
		radar ();
		Sleep (5);
	}

	return 0;
}

void updateEntityList ()
{
	DWORD start;
	start = Mem->FindSignature (clientDll, clientDllSize, (PBYTE)"\x05\x00\x00\x00\x00\xC1\xE9\x00\x39\x48\x04", "x????xx?xxx");
	DWORD p1 = Mem->ReadMem<DWORD> (start + 1);
	BYTE p2 = Mem->ReadMem<BYTE> (start + 7);
	entityList = (p1 + p2) - clientDll;
}

void updateLocalPlayer ()
{
	DWORD start;
	start = Mem->FindSignature (clientDll, clientDllSize, (PBYTE)"\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x00", "xxx????xx????xxxxx?");
	DWORD p1 = Mem->ReadMem<DWORD> (start + 0x3);
	DWORD p2 = Mem->ReadMem<BYTE> (start + 0x12);
	localPlayer = (p1 + p2) - clientDll;
}

void updateForceJump ()
{
	DWORD start;
	start = Mem->FindSignature (clientDll, clientDllSize, (PBYTE)"0x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x08\xA8\x08\xBF", "xx????xx????xxxxxxxxxxxx");
	forceJump = Mem->ReadMem<DWORD> (start + 0x2) - clientDll;
}

void radar ()
{
	for (int r = 0; r < 64; r++)
	{
		DWORD r_currentPlayer = Mem->ReadMem<DWORD> (clientDll + entityList + ((r - 1) * 16));
		bool r_currentPlayerDormant = Mem->ReadMem<bool> (r_currentPlayer + bDormant);
		bool r_currentPlayerbSpotted = Mem->ReadMem<bool> (r_currentPlayer + bSpotted);
		
		if (r_currentPlayerDormant)
			continue;
		else
		{
			if (!r_currentPlayerbSpotted)
				Mem->WriteMem<bool> (r_currentPlayer + bSpotted, 1);
			else
				continue;
		}
	}
}

void bhop ()
{
	if (GetAsyncKeyState (VK_SPACE) & 0x8000 && !isAir ())
	{
		Mem->WriteMem (clientDll + forceJump, 5);
	}
	else if (GetAsyncKeyState (VK_SPACE) & 0x8000 && isAir ())
	{
		Mem->WriteMem (clientDll + forceJump, 4);
		Mem->WriteMem (clientDll + forceJump, 5);
		Mem->WriteMem (clientDll + forceJump, 4);
	}
	else
	{
		Mem->WriteMem (clientDll + forceJump, 4);
	}
}

bool isAir ()
{
	int flag = Mem->ReadMem<int> (localPlayer + 0x100);
	std::cout << flag;
	return flag == 256 || flag == 258 || flag == 260 || flag == 262;
}

void log (std::string msg)
{
	if (msg.length () < 68)
	{
		int space = (68 - msg.length ()) / 2;
		std::cout << ("$ --- ");

		for (int i = 0; i < space; i++)
			std::cout << " ";

		std::cout << msg;

		for (int i = 0; i < space; i++)
			std::cout << " ";

		if (msg.length () % 2 != 0)
			std::cout << " ";

		std::cout << " --- $";
	}
	else
	{
		std::cout << msg;
	}
}