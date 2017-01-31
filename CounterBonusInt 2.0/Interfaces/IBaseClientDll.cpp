#pragma once

#include "IBaseClientDll.h"

ClientClass* IBaseClientDll::GetAllClasses ()
{
	typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
	return Utils::GetVFunc<OriginalFn> (this, 8)(this);
}