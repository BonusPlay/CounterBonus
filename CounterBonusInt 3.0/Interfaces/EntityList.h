#pragma once

#include "..\Utils\Toolbox.h"
#include "..\SDK\Entity.h"

class IEntityList
{
public:
	inline CEntity *getClientEntity (int i)
	{
		return Utils::getVFunc<CEntity *(__thiscall *)(void *, int)> (this, 3)(this, i);
	}

	inline CEntity *getEntityFromHandle (DWORD i)
	{
		return Utils::getVFunc<CEntity *(__thiscall *)(void *, int)> (this, 4)(this, i);
	}
};