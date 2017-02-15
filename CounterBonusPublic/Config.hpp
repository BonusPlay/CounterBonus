#pragma once

#include <Windows.h>
#include "json.hpp"

#ifdef max
#undef max
#endif

using json = nlohmann::json;

class cConfig
{
public:
	cConfig(json data);
	~cConfig();

	bool shutdown = false;
	void logAll();
	DWORD getLocalPlayer();
	DWORD getEntityList();
	DWORD getForceJump();

private:
	DWORD m_dwLocalPlayer;
	DWORD m_dwEntityList;
	DWORD m_dwForceJump;
};

extern cConfig* Config;