#pragma once

#include "..\sdk.h"

void Cheats::Run_Bhop ()
{
	if (Settings::Bhop && Global::UserCmd->buttons & IN_JUMP && !(Global::LocalPlayer->GetFlags () & FL_ONGROUND))
	{
		Global::UserCmd->buttons &= ~IN_JUMP;

		if (Settings::Strafe)
		{
			bool backwards = false; // Global::UserCmd->forwardmove < 0;

			if (Global::UserCmd->mousedx < 0)
				Global::UserCmd->sidemove = backwards ? 650.f : -650.f;

			if (Global::UserCmd->mousedx > 0)
				Global::UserCmd->sidemove = backwards ? -650.f : 650.f;
		}
	}
}

/*
if ((GetAsyncKeyState (VK_SPACE) && !(Global::LocalPlayer->GetFlags () & FL_ONGROUND)) && bKeysPressed)
{
if (pCmd->mousedx < 0)
{
pCmd->sidemove = -400.f;
}

if (pCmd->mousedx > 0)
{
pCmd->sidemove = 400.f;
}

if (bDirection)
{
pCmd->viewangles.y -= flYawBhop;
pCmd->sidemove = -400.f;
bDirection = false;
}
else
{
pCmd->viewangles.y += flYawBhop;
pCmd->sidemove = 400.f;
bDirection = true;
}
}
*/