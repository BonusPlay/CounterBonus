#pragma once

#include "..\Utils\Memory.h"
#include "..\Utils\Math.h"
#include "Offsets.h"
#include "Netvars.h"
#include "LocalPlayer.h"

class CEntity
{
public:
	inline CEntity* operator[] (int i)
	{
		Index = i;
		return this;
	}

	DWORD Base ();
	DWORD BoneBase ();
	int Health ();
	int Team ();
	int ClassID ();
	Vector3 Position ();
	Vector3 BonePos (int id);
	Vector3 Velocity ();
	bool Spotted ();
	void Spotted (bool value);
	float Distance ();
	//int GlowIndex ();
	int LifeState ();
	BYTE Flags ();
	bool OnGround ();
	//bool Dormant ();
	bool Valid ();

private:
	int Index;
};

CEntity Entity;