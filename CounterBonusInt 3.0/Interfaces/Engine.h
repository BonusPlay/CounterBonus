#pragma once

#include "..\Utils\Toolbox.h"

class IEngine
{
public:
	inline int getLocalPlayer ()
	{
		typedef int (__thiscall* OriginalFn)(void*);
		return Utils::getVFunc<OriginalFn> (this, 12)(this);
	}

	inline void getViewAngles (Vector &ang)
	{
		typedef void (__thiscall* OriginalFn)(void*, Vector&);
		return Utils::getVFunc<OriginalFn> (this, 18)(this, ang);
	}

	inline void setViewAngles (Vector &ang)
	{
		typedef void (__thiscall* OriginalFn)(void*, Vector&);
		return Utils::getVFunc<OriginalFn> (this, 19)(this, ang);
	}

	inline int getMaxClients ()
	{
		typedef int (__thiscall* OriginalFn)(void*);
		return Utils::getVFunc<OriginalFn> (this, 20)(this);
	}

	inline bool isInGame ()
	{
		typedef bool (__thiscall* OriginalFn)(void*);
		return Utils::getVFunc<OriginalFn> (this, 26)(this);
	}

	inline void getScreenSize (int &width, int &height)
	{
		typedef void (__thiscall* OriginalFn)(void*, int&, int&);
		return Utils::getVFunc<OriginalFn> (this, 5)(this, width, height);
	}

	const matrix4x4_t& WorldToScreenMatrix ()
	{
		typedef matrix4x4_t&(__thiscall* OriginalFn)(void*);
		return Utils::getVFunc<OriginalFn> (this, 37)(this);
	}
};