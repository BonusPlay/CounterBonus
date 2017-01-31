#pragma once

#include "Offsets.h"
#undef GetCurrentTime

class CGlobals
{
public:
	float GetCurrentTime ();
	float GetFrameTime ();
	int	  GetMaxClients ();
	float GetIntervalPerTick ();
	float GetInterpolationAmount ();
};

extern CGlobals* Globals;