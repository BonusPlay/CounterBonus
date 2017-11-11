#pragma once

#include "Hooks.hpp"

BOOL WINAPI DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls((HMODULE) hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) Hooks::Initialize, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		if (!lpReserved)
			Hooks::Restore();
		break;
	}

	return true;
}