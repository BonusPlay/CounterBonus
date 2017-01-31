#pragma once

#include "Cheats.h"

class CBhop
{
public:
	CBhop ();
	~CBhop ();

	void Start ();

private:
	bool isAir ();
};