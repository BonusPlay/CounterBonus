#pragma once

#include <Windows.h>

#include "..\Utils\Vector.h"
#include "..\Utils\Memory.h"
#include "..\Utils\Toolbox.h"

class CLocalPlayer
{
public:
	CLocalPlayer ();
	~CLocalPlayer ();

	DWORD local;

	void	getPlayer ();
	float*	getPos ();
	Vector	getVecPos ();
	float*	getPunch ();
	Vector	getVecPunch ();
	Vector	getVecEyePos ();
	float*	getEyePos ();
	float*	getClearEyePos ();
	Vector  getVecClearEyePos ();
	Vector	getVelocity ();
	int		getHealth ();
	int		getTeam ();
	int		getFlags ();
	int		getCrossID ();
	int		getShotsFired ();
	DWORD	getHandleWeap ();
	int		getWeapEnt ();
	DWORD	getCurrentWeapon ();
	int		getAmmo ();
	int		getWeaponId ();
	DWORD	getEnginePointer ();
	QAngle	getAngles ();
	float*	getFloatAngles ();
	Vector	getVecAngles ();
	void	setAngles (float *pfAngles);
	bool	isScoped ();
	bool	isNonRcsWeapon ();
	bool	isNonAimWeapon ();
	bool	air ();

private:
	bool	isWeaponPistol ();
	bool	isWeaponSniper ();
	bool	isWeaponKnife ();
	bool	isWeaponGrenade ();
	bool	isWeaponBomb ();
	bool	isWeaponTaser ();
	bool	isWeaponShotgun ();
};

extern CLocalPlayer* localPlayer;