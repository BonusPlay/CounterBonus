#pragma once

#include "IBaseClientDll.h"
#include "IClientEntityList.h"
#include "IClientMode.h"
#include "IEngineClient.h"

namespace Interfaces
{
	extern IBaseClientDll* Client;
	extern IClientEntityList* ClientEntityList;
	extern IClientMode* ClientMode;
	extern IEngineClient* Engine;
}