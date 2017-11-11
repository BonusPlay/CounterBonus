#include "dllmain.h"

BOOL WINAPI DllMain (HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason != DLL_PROCESS_ATTACH)
		return true;

	DisableThreadLibraryCalls ((HMODULE)hModule);

	if (!GetModuleHandle ("client.dll"))
		Sleep (300);
	if (!GetModuleHandle ("engine.dll"))
		Sleep (300);

	CreateThread (NULL, NULL, &Main, NULL, NULL, NULL);
	return true;
}

DWORD WINAPI Main (LPVOID params)
{
	msg = Utils::getExport<MsgFn> ("tier0.dll", "Msg");
	warning = Utils::getExport<WarningFn> ("tier0.dll", "Warning");

	makeLogo ();
	Settings = new CSettings ();

	I::Client		= Utils::createInterface<IBaseClientDll*> ("client.dll", "VClient018");
	I::Engine		= Utils::createInterface<IEngine*> ("engine.dll", "VEngineClient014");
	//I::Surface		= Utils::createInterface<ISurface*> ("vguimatsurface.dll", "VGUI_Surface031");
	I::EntityList	= Utils::createInterface<IEntityList*> ("client.dll", "VClientEntityList003");
	//I::CVar			= Utils::createInterface<ICVar*> ("vstdlib.dll", "VEngineCvar007");
	//I::InputSystem	= Utils::createInterface<IInputSystem*> ("inputsystem.dll", "InputSystemVersion001");
	//I::VPanel		= Utils::createInterface<IVPanel*> ("vgui2.dll", "VGUI_Panel009");

	DWORD* clientTable = (DWORD*)*(DWORD*)I::Client;
	I::ClientMode = **(IClientMode***)(Utils::findPattern (clientTable[ 10 ], 0x100, "\x8B\x0D????\x8B") + 0x02); //http://www.unknowncheats.me/forum/source-engine/159253-finding-pointer-clientmode-any-game.html
	//I::GlobalVars = **(IGlobalVars***)(Utils::findPattern (clientTable[ 0 ], 0x100, "\xA3") + 0x01); //http://www.unknowncheats.me/forum/source-engine/160691-finding-globalvars-internally-without-having-have-any-kinda-reversing-knowledge.html

	msg ("//===================================\\\\\n");
	msg ("||===================================||\n");
	msg ("|| Client      located at 0x1f7fcc60");
	msg ("|| Interfaces\n");
	msg ("|| Client      located at 0x%x ||\n", I::Client);
	msg ("|| Engine      located at 0x%x\n", I::Engine);
	//msg ("|| Surface     located at 0x%x\n", I::Surface);
	msg ("|| EntityList  located at 0x%x\n", I::EntityList);
	msg ("|| ClientMode  located at 0x%x\n", I::ClientMode);
	//msg ("|| GlobalVars  located at 0x%x\n", I::GlobalVars);
	//msg ("|| InputSystem located at 0x%x\n", I::InputSystem);
	//msg ("|| VPanel      located at 0x%x\n", I::VPanel);

	VMTBaseManager* clientModeHook = new VMTBaseManager ();
	clientModeHook->Init (I::ClientMode);
	clientModeHook->HookMethod (&Hooks::createMove, 24);
	clientModeHook->Rehook ();

	msg ("||=========================================\n");
	msg ("|| Hooks\n");
	msg ("|| CreateMove          at 0x%x\n", Hooks::createMove);

	//Menu->Setup ();

	return 0;
}

void makeLogo ()
{
	msg ("//=========================================================================================================\\\\\n");
	msg ("||                                                                                                         ||\n");
	msg ("||                   ______                  __            ____                                            ||\n");
	msg ("||                  / ____/___  __  ______  / /____  _____/ __ )____  ____  __  _______                    ||\n");
	msg ("||                 / /   / __ \\/ / / / __ \\/ __/ _ \\/ ___/ __  / __ \\/ __ \\/ / / / ___/                    ||\n");
	msg ("||                / /___/ /_/ / /_/ / / / / /_/  __/ /  / /_/ / /_/ / / / / /_/ (__  )                     ||\n");
	msg ("||                \\____/\\____/\\__,_/_/ /_/\\__/\\___/_/  /_____/\\____/_/ /_/\\__,_/____/                      ||\n");
	msg ("||                                                                                                         ||\n");
	msg ("||                                            ");
	warning ("proudly presented by BonusPlay");
	msg ("                               ||\n");
	msg ("||                                                                                                         ||\n");
	msg ("\\\\=========================================================================================================//\n");
}