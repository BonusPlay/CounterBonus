#include "dllmain.h"

BOOL WINAPI DllMain (HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls (hModule);
		CreateThread (NULL, NULL, Main, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	TerminateThread (Main, 0);

	return TRUE;
}

DWORD WINAPI Main (LPVOID params)
{
	Console = new CConsole ();
	cout << "Starting up" << endl;

	
	
	Console->~CConsole ();
	Sleep (1000);
	return 0;
}