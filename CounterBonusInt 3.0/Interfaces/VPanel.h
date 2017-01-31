#pragma once

#include "..\Utils\Toolbox.h"

class IVPanel
{
public:
	const char* GetName (int iPanel)
	{
		typedef const char*(__thiscall* OriginalFn)(void*, int);
		return Utils::getVFunc<OriginalFn> (this, 36)(this, iPanel);
	}
};