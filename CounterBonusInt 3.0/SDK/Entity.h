#pragma once

#include "..\Utils\Toolbox.h"

class CEntity
{
public:
	inline BYTE getLifeState ()
	{
		return Utils::readPtr<int> (this, 0x25B); //m_lifeState
	}

	inline int getFlags ()
	{
		return Utils::readPtr<int> (this, 0x100); //m_fFlags
	}

	inline Vector* getAimPunchAngle ()
	{
		return Utils::makePtr<Vector> (this, 0x301C); //m_Local + m_aimPunchAngle
	}

	inline Vector* getViewPunchAngle ()
	{
		return Utils::makePtr<Vector> (this, 0x3028); //m_Local + m_viewPunchAngle
	}

	inline int getTickBase ()
	{
		return Utils::readPtr<int> (this, 0x3424); //m_nTickBase
	}

	inline DWORD getActiveWeapon ()
	{
		return Utils::readPtr<DWORD> (this, 0x2EE8); //m_hActiveWeapon
	}

	inline Vector getVelocity ()
	{
		return Utils::readPtr<Vector> (this, 0x110); // m_vecVelocity
	}

	inline bool isDormant ()
	{
		return Utils::getVFunc<bool (__thiscall *)(void *)> ((this + 0x8), 9)((this + 0x8));
	}

	inline void *getModel ()
	{
		return Utils::getVFunc<void *(__thiscall *)(void *)> ((this + 0x4), 8)((this + 0x4));
	}

	inline Vector& getAbsOrigin ()
	{
		return Utils::getVFunc<Vector&(__thiscall *)(void *)> (this, 10)(this);
	}

	inline Vector getVecViewOffset ()
	{
		return Utils::readPtr<Vector> (this, 0x104); //m_vecViewOffset[0]
	}

	inline Vector getEyepos ()
	{
		return getAbsOrigin () + getVecViewOffset ();
	}

	inline bool setupBones (matrix3x4_t* bonematrix, int maxbones, int mask, float curtime = 0)
	{
		void* renderable = reinterpret_cast<void*>(reinterpret_cast<DWORD>(this) + 0x4);
		return Utils::getVFunc<bool (__thiscall *)(void*, matrix3x4_t*, int, int, float)> (renderable, 13)(renderable, bonematrix, maxbones, mask, curtime);
	}
};

extern CEntity *Entity;