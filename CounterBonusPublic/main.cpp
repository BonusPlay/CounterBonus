#pragma once
#include "Cheats.hpp"
#include "Config.hpp"
#include "Console.hpp"
#include "Memory.hpp"
#include "Network.hpp"
#include "Thread.hpp"

bool init();
bool work();
bool exit();

int main(int argc, char** argv)
{
	if (!init())
		return 1;
	
	if (!work())
		return 2;

	if (!exit())
		return 3;
}

bool init()
{
	Console = new cConsole();
	Thread = new cThreadManager();
	Network = new cNetworkManager();
	Memory = new cMemoryManager();
	while(Memory->clientDll == 0)
	{
		Memory->Process("csgo.exe");
		Memory->clientDll = Memory->Module("client.dll");
		Console->Message("Waiting for csgo...");
		Sleep(500);
	}

	return true;
}

bool work()
{
	Console->SetConsoleColor(dark_green, black);
	Console->RawMessage("/==============================================================================\\");
	Console->RawMessage("|       ______                  __            ____                             |");
	Console->RawMessage("|      / ____/___  __  ______  / /____  _____/ __ )____  ____  __  _______     |");
	Console->RawMessage("|     / /   / __ \\/ / / / __ \\/ __/ _ \\/ ___/ __  / __ \\/ __ \\/ / / / ___/     |");
	Console->RawMessage("|    / /___/ /_/ / /_/ / / / / /_/  __/ /  / /_/ / /_/ / / / / /_/ (__  )      |");
	Console->RawMessage("|    \\____/\\____/\\__,_/_/ /_/\\__/\\___/_/  /_____/\\____/_/ /_/\\__,_/____/       |");
	Console->RawMessage("|                                                                              |");
	Console->RawMessage("|                        proudly presented by BonusPlay                        |");
	Console->RawMessage("|                                                                              |");
	Console->RawMessage("\\==============================================================================/");
	Console->RawMessage("\n\n");
	Console->SetConsoleColor(white, black);

	json data = Network->getJson("https://api.bonusplay.pl/counterbonus");
	Config = new cConfig(data);

	printf("ClientDLL:     0x%02x\n", Memory->clientDll);
	Config->logAll();

	Thread->create("bhop", bhop);

	while (true)
	{
		if (GetAsyncKeyState(VK_F6))
			break;
		Sleep(500);
	}

	return true;
}

bool exit()
{
	Thread->endAll();
	delete Thread;

	delete Memory;
	delete Network;

	Sleep(500);
	delete Console;
	return true;
}

/*
#include <iostream>
#include <string>
#include <Windows.h>

#include "Memory.h"
#include "curl/curl.h"

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
	log ("CounterBonusPublic v. 1.3");
	Mem->Process ("csgo.exe");
	clientDll = Mem->Module ("client.dll");
	clientDllSize = Mem->ModuleSize ("client.dll");
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
	start = Mem->FindSignature (clientDll, clientDllSize, (PBYTE)"\x05\x00\x00\x00\x00\xC1\xe9\x00\x39\x48\x04", "x????xx?xxx");
	DWORD p1 = Mem->ReadMem<DWORD>(start + 0x1);
	DWORD p2 = Mem->ReadMem<DWORD>(start + 0x7);
	entityList = (p1 + p2) - clientDll;
}

void updateLocalPlayer ()
{
	DWORD start;
	start = Mem->FindSignature (clientDll, clientDllSize, (PBYTE)"\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A", "x????xx????????x????xxx");
	DWORD p1 = Mem->ReadMem<DWORD> (start + 0x3);
	DWORD p2 = Mem->ReadMem<BYTE> (start + 0x12);
	localPlayer = (p1 + p2) - clientDll;
}

void updateForceJump ()
{
	DWORD start;
	start = Mem->FindSignature (clientDll, clientDllSize, (PBYTE)"\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x08", "xx????xx????xxxxxxxx");
	forceJump = Mem->ReadMem<DWORD> (start + 0x2) - clientDll;
}

void radar ()
{
	for (int r = 0; r < 64; r++)
	{
		DWORD r_currentPlayer = Mem->ReadMem<DWORD> (clientDll + entityList + ((r - 1) * 16));
		bool r_currentPlayerDormant = Mem->ReadMem<bool> (r_currentPlayer + bDormant);
		bool r_currentPlayerbSpotted = Mem->ReadMem<bool> (r_currentPlayer + bSpotted);
		
		if (!r_currentPlayerDormant)
		{
			if (!r_currentPlayerbSpotted)
				Mem->WriteMem<bool> (r_currentPlayer + bSpotted, 1);
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
*/