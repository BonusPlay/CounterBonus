#pragma once

#include "..\SDK\CVar.h"
#include "..\Utils\Toolbox.h"

class ICVar
{
public:
	void RegisterConCommand (CVar *pCvar)
	{
		typedef void (__thiscall* OriginalFn)(void*, CVar*);
		return Utils::getVFunc<OriginalFn> (this, 1)(this, pCvar);
	}

	CVar* FindVar (const char *var_name)
	{
		typedef CVar*(__thiscall* OriginalFn)(void*, const char*);
		return Utils::getVFunc<OriginalFn> (this, 15)(this, var_name);
	}
};