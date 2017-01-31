#include "CreateMove.h"

bool __fastcall Hooks::createMove (void* thishook, void*, float frametime, CUserCMD* cmd)
{
	if (cmd->command_number == 0) //if command_number is 0 then ExtraMouseSample is being called
		return 0;

	CEntity* localPlayer = I::EntityList->getClientEntity (I::Engine->getLocalPlayer ());

	if (!localPlayer)
		return 0;

	// Bhop
	
	if (cmd->buttons &IN_JUMP && (!(localPlayer->getFlags () &FL_ONGROUND)))
		cmd->buttons &= ~IN_JUMP;

	// Autostrafe
	if (!(localPlayer->getFlags () & FL_ONGROUND))
		if (cmd->mousedx > 1 || cmd->mousedx < -1)
			cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;

	return 0; //return 1 if you want to call engine->SetViewAngles
}