#pragma once
#include "Config.hpp"

#include <cstdlib>

#include "Console.hpp"

#pragma region Singleton
cConfig* Config;

cConfig::cConfig(json data)
{
	Console->DebugMessage("Config starting up");
	m_dwLocalPlayer = std::strtoul(data["m_dwLocalPlayer"].get<std::string>().c_str(), NULL, 16);
	m_dwEntityList	= std::strtoul(data["m_dwEntityList"].get<std::string>().c_str(), NULL, 16);
	m_dwForceJump	= std::strtoul(data["m_dwForceJump"].get<std::string>().c_str(), NULL, 16);
}

cConfig::~cConfig()
{
	Console->DebugMessage("Config shutting down");
}

#pragma endregion

void cConfig::logAll()
{
	printf("LocalPlayer:    0x%02x\n", m_dwLocalPlayer);
	printf("EntityList:     0x%02x\n", m_dwEntityList);
	printf("ForceJump:      0x%02x\n", m_dwForceJump);
}

DWORD cConfig::getLocalPlayer()
{
	return m_dwLocalPlayer;
}

DWORD cConfig::getEntityList()
{
	return m_dwEntityList;
}

DWORD cConfig::getForceJump()
{
	return m_dwForceJump;
}