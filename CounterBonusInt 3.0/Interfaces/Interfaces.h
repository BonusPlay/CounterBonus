#pragma once

#include "BaseClientDll.h"
#include "ClientMode.h"
#include "Engine.h"
#include "Surface.h"
#include "EntityList.h"
#include "ICVar.h"
#include "InputSystem.h"
#include "GlobalVars.h"
#include "VPanel.h"

namespace I
{
	extern IBaseClientDll* Client;
	extern IClientMode* ClientMode;
	extern IEngine* Engine;
	extern ISurface* Surface;
	extern IEntityList* EntityList;
	extern ICVar* CVar;
	extern IInputSystem* InputSystem;
	extern IGlobalVars* GlobalVars;
	extern IVPanel* VPanel;
}