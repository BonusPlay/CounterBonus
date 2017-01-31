#include "Toolbox.h"

CConsole* Utils::Console;
CNetVarManager* Utils::NetVarManager;
COffsets Utils::Offsets;

CBaseEntity* Global::LocalPlayer = NULL;
CUserCmd* Global::UserCmd = NULL;

bool Settings::Aimbot = false;
bool Settings::Bhop = false;
bool Settings::Strafe = false;

bool bCompare (const BYTE* Data, const BYTE* Mask, const char* szMask)
{
	for (; *szMask; ++szMask, ++Mask, ++Data)
	{
		if (*szMask == 'x' && *Mask != *Data)
		{
			return false;
		}
	}
	return (*szMask) == 0;
}

void* Utils::Hook (void* pInstance, int iIndex, void* pHookFunc)
{
	DWORD dwVTable = *(DWORD*)pInstance;
	DWORD dwVFunc = dwVTable + sizeof (DWORD) * iIndex;
	intptr_t pOrigFunc = *((DWORD*)dwVFunc);
	DWORD dwOldProtect;
	VirtualProtect ((LPVOID)dwVFunc, sizeof (DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD*)dwVFunc) = (DWORD)pHookFunc;
	VirtualProtect ((LPVOID)dwVFunc, sizeof (DWORD), dwOldProtect, &dwOldProtect);

	return (void*)pOrigFunc;
}

void Utils::Unhook (void* pInstance, int iIndex, void* pOriginal)
{
	DWORD dwVTable = *(DWORD*)pInstance;
	DWORD dwVFunc = dwVTable + sizeof (DWORD)* iIndex;
	intptr_t pOrigFunc = *((DWORD*)dwVFunc);
	DWORD dwOldProtect;
	VirtualProtect ((LPVOID)dwVFunc, sizeof (DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD*)dwVFunc) = (DWORD)pOriginal;
	VirtualProtect ((LPVOID)dwVFunc, sizeof (DWORD), dwOldProtect, &dwOldProtect);
}

DWORD Utils::FindPattern (std::string moduleName, BYTE* Mask, char* szMask)
{
	DWORD dwAddress = (DWORD)GetModuleHandleA (moduleName.c_str ());

	MODULEINFO miModInfo; GetModuleInformation (GetCurrentProcess (), (HMODULE)dwAddress, &miModInfo, sizeof (MODULEINFO));
	DWORD dwLength = miModInfo.SizeOfImage;
	for (DWORD i = 0; i < dwLength; i++)
	{
		if (bCompare ((BYTE*)(dwAddress + i), Mask, szMask))
		{
			return (DWORD)(dwAddress + i);
		}
	}
	return 0;
}

CBaseEntity* Utils::GetLocalPlayer ()
{
	return Interfaces::ClientEntityList->GetClientEntity (Interfaces::Engine->GetLocalPlayer ());
}