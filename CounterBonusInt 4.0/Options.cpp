#pragma once

#include "Options.hpp"

namespace Options
{
	extern bool g_bMainWindowOpen = false;
	extern bool g_bXRCSEnabled = false;

	// AIM
	extern bool g_bRCSEnabled = false;

	// VISUAL
	extern bool g_bESPEnabled = false;
	extern bool g_bESPAllyHitboxesEnabled = false;
	extern bool g_bESPAllyNamesEnabled = false;
	extern bool g_bESPEnemyHitboxesEnabled = false;
	extern bool g_bESPEnemyNamesEnabled = false;
	extern float g_bESPAllyColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	extern float g_bESPEnemyColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	// MISC
	extern bool g_bBHopEnabled = false;
}
