#include "CVar.h"

#include "..\Utils\Toolbox.h"

void CVar::SetValue (const char* value)
{
	typedef void (__thiscall* OriginalFn)(void*, const char*);
	return Utils::getVFunc<OriginalFn> (this, 14)(this, value);
}

void CVar::SetValue (float value)
{
	typedef void (__thiscall* OriginalFn)(void*, float);
	return Utils::getVFunc<OriginalFn> (this, 15)(this, value);
}

void CVar::SetValue (int value)
{
	typedef void (__thiscall* OriginalFn)(void*, int);
	return Utils::getVFunc<OriginalFn> (this, 16)(this, value);
}

void CVar::SetValue (Color value)
{
	typedef void (__thiscall* OriginalFn)(void*, Color);
	return Utils::getVFunc<OriginalFn> (this, 17)(this, value);
}

char* CVar::GetName ()
{
	typedef char*(__thiscall* OriginalFn)(void*);
	return Utils::getVFunc<OriginalFn> (this, 5)(this);
}

char* CVar::GetDefault ()
{
	return pszDefaultValue;
}