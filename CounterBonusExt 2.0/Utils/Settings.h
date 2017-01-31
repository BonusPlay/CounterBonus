#pragma once

#include <Windows.h>

class CSettings
{
public:
	CSettings ();
	~CSettings ();

	DWORD bhopKey		= VK_SPACE;
	DWORD triggerKey	= 0x43; // C
	DWORD aimKey		= 0x56; // V

	float aimSmooth = 180;
	int shootWait	= 0;

	float pitchMinPunch = 1;
	float pitchMaxPunch = 1;
	float yawMinPunch	= 1;
	float yawMaxPunch	= 1;
};

extern CSettings* Settings;