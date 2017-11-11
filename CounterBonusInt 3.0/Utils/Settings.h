#pragma once

class CSettings
{
public:
	// bhop
	bool b_bhop_enabled = false;

	// autostrafe
	bool b_autostrafe_enabled = false;
};

extern CSettings* Settings;