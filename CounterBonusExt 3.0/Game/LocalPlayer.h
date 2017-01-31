#pragma once

#include "Offsets.h"
#include "Netvars.h"
#include "Enums.h"
#include "..\Utils\Math.h"

class CLocalPlayer
{
public:
	DWORD Base ();
	int Health ();
	int Team ();
	int CrosshairID ();
	int ActiveWeaponBase ();
	int ShotsFired ();
	Vector3 Position ();
	Vector3 Angles ();
	void Angles (Vector3 value);
	Vector3 EyePos ();
	Vector3 Velocity ();
	//Vector3 Punch ();
	float FlashDuration ();
	BYTE Flags ();
	bool OnGround ();
	bool Jumping ();
	bool Zoomed ();

	void Jump ();
	void unJump ();

	//Weapons WeaponList;
};

extern CLocalPlayer* LocalPlayer;