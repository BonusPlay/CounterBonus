#pragma once
#include "rcs.hpp"

#include "../Game/CSPlayer.hpp"
#include "../Options.hpp"
#include "../Utils/Toolbox.hpp"

void rcs(SourceEngine::CUserCmd* pCmd)
{
	//RCS
	if (Options::g_bRCSEnabled)
	{
		C_CSPlayer* pLocal = C_CSPlayer::GetLocalPlayer();

		SourceEngine::Vector punchAngles = *pLocal->AimPunch() * 2.0f;

		if (punchAngles.x != 0.0f || punchAngles.y != 0)
		{
			pCmd->viewangles -= punchAngles;
			if (!Toolbox::getInstance()->Clamp(pCmd->viewangles))
				abort(); //Failed to clamp angles!!1! ABOOOOOORT
		}
	}
	else if(Options::g_bXRCSEnabled)
	{
		C_CSPlayer* pLocal = C_CSPlayer::GetLocalPlayer();

		SourceEngine::Vector punchAngles = *pLocal->AimPunch();
		punchAngles.y = punchAngles.y * 2.0f;

		if (punchAngles.x != 0.0f || punchAngles.y != 0)
		{
			pCmd->viewangles -= punchAngles;
			if (!Toolbox::getInstance()->Clamp(pCmd->viewangles))
				abort(); //Failed to clamp angles!!1! ABOOOOOORT
		}
	}
}