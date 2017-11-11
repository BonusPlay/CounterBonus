#pragma once

#include "..\Utils\Toolbox.h"

class IInputSystem
{
public:
	void EnableInput (bool bEnable)
	{
		typedef void (__thiscall* OriginalFn)(void*, bool);
		return Utils::getVFunc<OriginalFn> (this, 11)(this, bEnable);
	}

	void ResetInputState ()
	{
		typedef void (__thiscall* OriginalFn)(void*);
		return Utils::getVFunc<OriginalFn> (this, 39)(this);
	}
};