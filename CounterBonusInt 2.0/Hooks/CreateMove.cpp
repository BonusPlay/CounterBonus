#pragma once

#include "CreateMove.h"

bool __stdcall Hooks::CreateMove (float flInputSampleTime, CUserCmd* cmd)
{
	Global::LocalPlayer = Utils::GetLocalPlayer ();

	if (cmd->command_number == 0)
		return false;

	if (Global::LocalPlayer)
	{
		Cheats::Run_Bhop ();
	}

	cmd->viewangles.Normalize ();
	return true;
}