#pragma once

#include "Console.h"
#include "netvars\netvars.h"
#include "offsets\offsets.h"

bool bCompare (const BYTE* Data, const BYTE* Mask, const char* szMask);

namespace Utils
{
	extern CConsole* Console;
	extern CNetVarManager* NetVarManager;
	extern COffsets Offsets;

	extern DWORD FindPattern (std::string moduleName, BYTE* Mask, char* szMask);
	extern CBaseEntity* GetLocalPlayer ();
	extern void* Hook (void* pInstance, int iIndex, void* pHookFunc);
	extern void Unhook (void* pInstance, int iIndex, void* pHookFunc);

	template <typename T>
	T* CaptureInterface (std::string strModule, std::string strInterface)
	{
		typedef T* (*CreateInterfaceFn)(const char* szName, int iReturn);
		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress (GetModuleHandleA (strModule.c_str ()), "CreateInterface");

		return CreateInterface (strInterface.c_str (), 0);
	}

	template <typename T>
	T GetVFunc (void *vTable, int iIndex)
	{
		return (*(T**)vTable)[ iIndex ];
	}
}

namespace Global
{
	extern CBaseEntity* LocalPlayer;
	extern CUserCmd* UserCmd;
}

namespace Settings
{
	extern bool Aimbot;
	extern bool Bhop;
	extern bool Strafe;
}