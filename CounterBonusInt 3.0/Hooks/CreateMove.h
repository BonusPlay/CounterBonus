#pragma once

#include "..\SDK\CUserCMD.h"
#include "..\SDK\Entity.h"
#include "..\SDK\Enums.h"

#include "..\Interfaces\Interfaces.h"
#include "..\Utils\Settings.h"

namespace Hooks
{
	bool __fastcall createMove (void* thishook, void*, float frametime, CUserCMD* cmd);
}