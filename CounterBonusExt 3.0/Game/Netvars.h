#pragma once

#include "Offsets.h"

class CNetVars
{
public:
	CNetVars ();
	~CNetVars ();
	void Log ();

	DWORD m_hOwnerEntity;
	DWORD m_iTeamNum;
	DWORD m_ArmorValue;
	DWORD m_vecOrigin;
	DWORD m_vecVelocity;
	DWORD m_vecViewOffset;
	DWORD m_iShotsFired;
	DWORD m_bHasDefuser;
	DWORD m_bIsDefusing;
	DWORD m_bHasHelmet;
	DWORD m_flFlashDuration;
	DWORD m_flFlashMaxAlpha;
	DWORD m_iLifeState;
	DWORD m_fFlags;
	DWORD m_iObserverMode;
	DWORD m_hObserverTarget;
	DWORD m_iClass;
	DWORD m_iHealth;
	DWORD m_iFOVStart;
	DWORD m_hActiveWeapon;
	DWORD m_fImmuneToGun;
	DWORD m_bSpottedByMask;
	DWORD m_iCompetitiveRanking;
	DWORD m_iCompetitiveWins;
	DWORD m_AttributeManager;
	DWORD m_Item;
	DWORD m_iItemDefinitionIndex;
	DWORD m_bSpotted;
	DWORD m_iClip1;
	DWORD m_iClip2;
	DWORD m_fAccuracyPenalty;
	DWORD m_dwBoneMatrix;
	DWORD m_bBombTicking;
	DWORD m_flC4Blow;
	DWORD m_nTickBase;
	DWORD m_szLastPlaceName;
	DWORD m_iMatchStats_MoneySaved;
	DWORD m_flNextPrimaryAttack;

private:
	DWORD inline GetNetVar (const char* szClassName, const char* szNetVar);
};

extern CNetVars* NetVars;