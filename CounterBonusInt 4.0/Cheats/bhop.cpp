#pragma once
#include "bhop.hpp"

#include "../Game/CSPlayer.hpp"
#include "../Options.hpp"

void bhop(SourceEngine::CUserCmd* pCmd)
{
	if (Options::g_bBHopEnabled)
	{
		C_CSPlayer* pLocal = C_CSPlayer::GetLocalPlayer();

		//If the player is pressing the JUMP button AND we are on not on ground
		if ((pCmd->buttons & IN_JUMP) && !(pLocal->GetFlags() & (int)FL_ONGROUND))
			pCmd->buttons &= ~IN_JUMP;
	}
}