#pragma once

#include "CreateMove.h"

extern CreateMoveFn oCreateMove;

namespace Hooks
{
	extern bool __stdcall CreateMove (float flInputSampleTime, CUserCmd* cmd);
}