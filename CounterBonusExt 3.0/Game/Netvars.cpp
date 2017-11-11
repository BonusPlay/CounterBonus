#include "Netvars.h"

CNetVars* NetVars;

CNetVars::CNetVars ()
{
	Console->DebugMessage ("NetVarHelper starting up");

	m_hOwnerEntity = GetNetVar ("DT_BaseEntity", "m_hOwnerEntity");
	m_iTeamNum = GetNetVar ("DT_BaseEntity", "m_iTeamNum");
	m_ArmorValue = GetNetVar ("DT_CSPlayer", "m_ArmorValue");
	m_vecOrigin = GetNetVar ("DT_CSPlayer", "m_vecOrigin");
	m_vecVelocity = GetNetVar ("DT_CSPlayer", "m_vecVelocity[0]");
	m_vecViewOffset = GetNetVar ("DT_CSPlayer", "m_vecViewOffset[0]");
	m_iShotsFired = GetNetVar ("DT_CSPlayer", "m_iShotsFired");
	m_bHasDefuser = GetNetVar ("DT_CSPlayer", "m_bHasDefuser");
	m_bIsDefusing = GetNetVar ("DT_CSPlayer", "m_bIsDefusing");
	m_bHasHelmet = GetNetVar ("DT_CSPlayer", "m_bHasHelmet");
	m_flFlashDuration = GetNetVar ("DT_CSPlayer", "m_flFlashDuration");
	m_flFlashMaxAlpha = GetNetVar ("DT_CSPlayer", "m_flFlashMaxAlpha");
	m_iLifeState = GetNetVar ("DT_CSPlayer", "m_lifeState");
	m_fFlags = GetNetVar ("DT_CSPlayer", "m_fFlags");
	m_iObserverMode = GetNetVar ("DT_CSPlayer", "m_iObserverMode");
	m_hObserverTarget = GetNetVar ("DT_CSPlayer", "m_hObserverTarget");
	m_iClass = GetNetVar ("DT_CSPlayer", "m_iClass");
	m_iHealth = GetNetVar ("DT_CSPlayer", "m_iHealth");
	m_iFOVStart = GetNetVar ("DT_CSPlayer", "m_iFOVStart");
	m_hActiveWeapon = GetNetVar ("DT_CSPlayer", "m_hActiveWeapon");
	m_fImmuneToGun = GetNetVar ("DT_CSPlayer", "m_fImmuneToGunGameDamageTime");
	m_bSpottedByMask = GetNetVar ("DT_BaseEntity", "m_bSpottedByMask");
	m_iCompetitiveRanking = GetNetVar ("DT_CSPlayerResource", "m_iCompetitiveRanking");
	m_iCompetitiveWins = GetNetVar ("DT_CSPlayerResource", "m_iCompetitiveWins");
	m_AttributeManager = GetNetVar ("DT_BaseAttributableItem", "m_AttributeManager");
	m_Item = GetNetVar ("DT_BaseAttributableItem", "m_Item");
	m_iItemDefinitionIndex = GetNetVar ("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	m_bSpotted = GetNetVar ("DT_BaseAttributableItem", "m_bSpotted");
	m_iClip1 = GetNetVar ("DT_BaseCombatWeapon", "m_iClip1");
	m_iClip2 = GetNetVar ("DT_BaseCombatWeapon", "m_iClip2");
	m_fAccuracyPenalty = GetNetVar ("DT_WeaponAK47", "m_fAccuracyPenalty");
	m_dwBoneMatrix = GetNetVar ("DT_BaseAnimating", "m_nForceBone") + 0x1C;
	m_bBombTicking = GetNetVar ("DT_PlantedC4", "m_bBombTicking");
	m_flC4Blow = GetNetVar ("DT_PlantedC4", "m_flC4Blow");
	m_nTickBase = GetNetVar ("DT_BasePlayer", "m_nTickBase");
	m_szLastPlaceName = GetNetVar ("DT_BasePlayer", "m_szLastPlaceName");
	m_iMatchStats_MoneySaved = GetNetVar ("DT_CSPlayer", "m_iMatchStats_MoneySaved");
	m_flNextPrimaryAttack = GetNetVar ("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
}

void CNetVars::Log ()
{
	Console->SuccessMessage ("[NetVar Manager] Netvars:");
	cout << "> m_hOwnerEntity           = 0x" << hex << uppercase << m_hOwnerEntity << nouppercase << endl;
	cout << "> m_iTeamNum               = 0x" << hex << uppercase << m_iTeamNum << nouppercase << endl;
	cout << "> m_ArmorValue             = 0x" << hex << uppercase << m_ArmorValue << nouppercase << endl;
	cout << "> m_vecOrigin              = 0x" << hex << uppercase << m_vecOrigin << nouppercase << endl;
	cout << "> m_vecVelocity            = 0x" << hex << uppercase << m_vecVelocity << nouppercase << endl;
	cout << "> m_vecViewOffset          = 0x" << hex << uppercase << m_vecViewOffset << nouppercase << endl;
	cout << "> m_iShotsFired            = 0x" << hex << uppercase << m_iShotsFired << nouppercase << endl;
	cout << "> m_bHasDefuser            = 0x" << hex << uppercase << m_bHasDefuser << nouppercase << endl;
	cout << "> m_bIsDefusing            = 0x" << hex << uppercase << m_bIsDefusing << nouppercase << endl;
	cout << "> m_bHasHelmet             = 0x" << hex << uppercase << m_bHasHelmet << nouppercase << endl;
	cout << "> m_flFlashDuration        = 0x" << hex << uppercase << m_flFlashDuration << nouppercase << endl;
	cout << "> m_flFlashMaxAlpha        = 0x" << hex << uppercase << m_flFlashMaxAlpha << nouppercase << endl;
	cout << "> m_iLifeState             = 0x" << hex << uppercase << m_iLifeState << nouppercase << endl;
	cout << "> m_fFlags                 = 0x" << hex << uppercase << m_fFlags << nouppercase << endl;
	cout << "> m_iObserverMode          = 0x" << hex << uppercase << m_iObserverMode << nouppercase << endl;
	cout << "> m_hObserverTarget        = 0x" << hex << uppercase << m_hObserverTarget << nouppercase << endl;
	cout << "> m_iClass                 = 0x" << hex << uppercase << m_iClass << nouppercase << endl;
	cout << "> m_iHealth                = 0x" << hex << uppercase << m_iHealth << nouppercase << endl;
	cout << "> m_iFOVStart              = 0x" << hex << uppercase << m_iFOVStart << nouppercase << endl;
	cout << "> m_hActiveWeapon          = 0x" << hex << uppercase << m_hActiveWeapon << nouppercase << endl;
	cout << "> m_fImmuneToGun           = 0x" << hex << uppercase << m_fImmuneToGun << nouppercase << endl;
	cout << "> m_bSpottedByMask         = 0x" << hex << uppercase << m_bSpottedByMask << nouppercase << endl;
	cout << "> m_iCompetitiveRanking    = 0x" << hex << uppercase << m_iCompetitiveRanking << nouppercase << endl;
	cout << "> m_iCompetitiveWins       = 0x" << hex << uppercase << m_iCompetitiveWins << nouppercase << endl;
	cout << "> m_AttributeManager       = 0x" << hex << uppercase << m_AttributeManager << nouppercase << endl;
	cout << "> m_Item                   = 0x" << hex << uppercase << m_Item << nouppercase << endl;
	cout << "> m_iItemDefinitionIndex   = 0x" << hex << uppercase << m_iItemDefinitionIndex << nouppercase << endl;
	cout << "> m_bSpotted               = 0x" << hex << uppercase << m_bSpotted << nouppercase << endl;
	cout << "> m_iClip1                 = 0x" << hex << uppercase << m_iClip1 << nouppercase << endl;
	cout << "> m_iClip2                 = 0x" << hex << uppercase << m_iClip2 << nouppercase << endl;
	cout << "> m_fAccuracyPenalty       = 0x" << hex << uppercase << m_fAccuracyPenalty << nouppercase << endl;
	cout << "> m_dwBoneMatrix           = 0x" << hex << uppercase << m_dwBoneMatrix << nouppercase << endl;
	cout << "> m_bBombTicking           = 0x" << hex << uppercase << m_bBombTicking << nouppercase << endl;
	cout << "> m_flC4Blow               = 0x" << hex << uppercase << m_flC4Blow << nouppercase << endl;
	cout << "> m_nTickBase              = 0x" << hex << uppercase << m_nTickBase << nouppercase << endl;
	cout << "> m_szLastPlaceName        = 0x" << hex << uppercase << m_szLastPlaceName << nouppercase << endl;
	cout << "> m_iMatchStats_MoneySaved = 0x" << hex << uppercase << m_iMatchStats_MoneySaved << nouppercase << endl;
	cout << "> m_flNextPrimaryAttack    = 0x" << hex << uppercase << m_flNextPrimaryAttack << nouppercase << endl;
}

CNetVars::~CNetVars ()
{
	Console->DebugMessage ("NetVarManager shutting down");
}

class CRecvTable
{
public:
	class CRecvProp
	{
	public:
		const char* GetVarName ()
		{
			DWORD offset = Memory->Read<DWORD> ((DWORD)this);
			char varName[ 128 ];
			Memory->ReadCustom (offset, varName, 128);
			return varName;
		}

		int GetOffset ()
		{
			return Memory->Read<int> ((DWORD)this + 0x2C);
		}
		CRecvTable* GetDataTable ()
		{
			return Memory->Read<CRecvTable*> ((DWORD) this + 0x28);
		}
	};

	const char* GetTableName ()
	{
		DWORD offset = Memory->Read<DWORD> ((DWORD)this + 0xC);
		char tableName[ 128 ];
		Memory->ReadCustom (offset, tableName, 128);
		return tableName;
	}

	int GetMaxProp ()
	{
		return Memory->Read<int> ((DWORD)this + 0x4);
	}

	CRecvProp* GetProperty (int iIndex)
	{
		return (CRecvProp*)(Memory->Read<DWORD> ((DWORD) this) + 0x3C * iIndex);
	}

};

class ClientClass
{
public:
	const char* GetNetworkName ()
	{
		DWORD offset = Memory->Read<DWORD> ((DWORD)this + 0x8);
		char networkName[ 128 ];
		Memory->ReadCustom (offset, networkName, 128);
		return networkName;
	}

	ClientClass* GetNextClass ()
	{
		return Memory->Read<ClientClass*> ((DWORD)this + 0x10);
	}

	CRecvTable* GetTable ()
	{
		return Memory->Read<CRecvTable*> ((DWORD) this + 0xC);
	}
};

DWORD inline CNetVars::GetNetVar (const char* szClassName, const char* szNetVar)
{
	if (!Offsets->m_dwNetvarClasses || !szClassName || !szNetVar)
		Console->ErrorMessage ("Classes are fucked. Can't grab NetVars");

	ClientClass* pClass = (ClientClass*)Offsets->m_dwNetvarClasses;

	if (!pClass)
	{
		return NULL;
	}

	for (; pClass; pClass = pClass->GetNextClass ())
	{
		if (strcmp (szClassName, pClass->GetTable ()->GetTableName ()))
			continue;

		for (int i = 0; i < pClass->GetTable ()->GetMaxProp (); i++)
		{
			CRecvTable::CRecvProp* pRecvProp = pClass->GetTable ()->GetProperty (i);

			if (isdigit (pRecvProp->GetVarName ()[ 0 ]))
				continue;

			if (!strcmp (pRecvProp->GetVarName (), szNetVar))
			{
				return pRecvProp->GetOffset ();
			}

			if (!pRecvProp->GetDataTable ())
				continue;

			for (int j = 0; j < pRecvProp->GetDataTable ()->GetMaxProp (); ++j)
			{
				CRecvTable::CRecvProp* pRecvProp2 = pRecvProp->GetDataTable ()->GetProperty (j);

				if (isdigit (pRecvProp2->GetVarName ()[ 0 ]))
					continue;

				if (!strcmp (pRecvProp2->GetVarName (), szNetVar))
				{
					return pRecvProp2->GetOffset ();
				}

				if (!pRecvProp2->GetDataTable ())
					continue;

				for (int k = 0; k < pRecvProp2->GetDataTable ()->GetMaxProp (); ++k)
				{
					CRecvTable::CRecvProp* pRecvProp3 = pRecvProp2->GetDataTable ()->GetProperty (k);

					if (isdigit (pRecvProp3->GetVarName ()[ 0 ]))
						continue;

					if (!strcmp (pRecvProp3->GetVarName (), szNetVar))
					{
						return pRecvProp3->GetOffset ();
					}
				}
			}
		}
	}

	return NULL;
}