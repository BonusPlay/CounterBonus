#include "dllmain.h"

BOOL WINAPI DllMain (HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason != DLL_PROCESS_ATTACH)
		return true;

	Utils::Console = new CConsole ();

	if (!GetModuleHandle ("client.dll"))
		Sleep (300);
	if (!GetModuleHandle ("engine.dll"))
		Sleep (300);

	CreateThread (NULL, NULL, &Main, NULL, NULL, NULL);
}

DWORD WINAPI Main (LPVOID params)
{
	Interfaces::Client = Utils::CaptureInterface<IBaseClientDll> ("client.dll", "VClient017");
	Interfaces::ClientEntityList = Utils::CaptureInterface<IClientEntityList> ("client.dll", "VClientEntityList003");
	Interfaces::ClientMode = **(IClientMode***)((*(DWORD**)Interfaces::Client)[ 10 ] + 0x5);
	Interfaces::Engine = Utils::CaptureInterface<IEngineClient> ("engine.dll", "VEngineClient013");

	Utils::NetVarManager = new CNetVarManager ();
	Offsets::GrabOffsets ();

	oCreateMove = (CreateMoveFn)Utils::Hook (Interfaces::ClientMode, 24, Hooks::CreateMove);

	return 0;
}