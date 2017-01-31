#pragma once

#include <Windows.h>

class COffsets
{
public:
	COffsets ();
	~COffsets ();

	DWORD clientDll;
	DWORD clientDllSize;
	DWORD engineDll;
	DWORD engineDllSize;

	//autoupdate
	DWORD LocalPlayer;
	DWORD EntityList;
	DWORD Attack;
	DWORD Jump;
	DWORD CrosshairID;
	DWORD GlowObject;
	DWORD ViewMatrix;

	DWORD ClientState;
	DWORD ViewAngles;
	DWORD bSendPackets = 0xF1797;

	//selfupdate
	DWORD m_fFlags = 0x100;
	DWORD m_bSpotted = 0x935;
	DWORD m_hActiveWeapon = 0x2EC8;
	DWORD m_iTeamNum = 0xF0;
	DWORD m_iHealth = 0xFC;
	DWORD m_vecOrigin = 0x134;
	DWORD m_vecVelocity = 0x110;
	DWORD m_vecPunch = 0x2FF8;
	DWORD m_iClip1 = 0x31D4;
	DWORD m_dwBoneMatrix = 0x267C;
	DWORD m_lifeState = 0x25B;
	DWORD m_vecViewOffset = 0x104;
	DWORD m_iShotsFired = 0xA280;
	DWORD m_bDormant = 0xE9;
	DWORD m_flFlashMaxAlpha = 0xA2C4;
	DWORD m_iGlowIndex = 0xA2E0;
	DWORD m_flNextPrimaryAttack = 0x31A8;
	DWORD m_bIsScoped = 0x385C;
	DWORD m_iFOV = 0x31A8;

	//weapon
	DWORD m_nModelIndex = 0x254;
	DWORD m_iItemDefinitionIndex = 0x2F60;
	DWORD m_iViewModelIndex = 0x31B0;
	DWORD m_iWorldModelIndex = 0x31B4;
	DWORD m_iWorldDroppedModelIndex = 0x31B8;
};

extern COffsets* Offsets;