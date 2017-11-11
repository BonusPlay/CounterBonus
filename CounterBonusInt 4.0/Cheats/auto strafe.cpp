#pragma once
#include "auto strafe.hpp"

#include "../Game/CSPlayer.hpp"
#include "../Options.hpp"

void autostrafe(SourceEngine::CUserCmd* pCmd)
{
	if(Options::g_bAutoStrafeEnabled)
	{
		C_CSPlayer* pLocal = C_CSPlayer::GetLocalPlayer();

		if (pLocal->GetFlags() & FL_ONGROUND)
			return;

		if (pCmd->mousedx > 1 || pCmd->mousedx < -1)
			pCmd->sidemove = pCmd->mousedx < 0.f ? -400.f : 400.f;
	}
}