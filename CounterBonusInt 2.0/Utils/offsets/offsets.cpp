#include "offsets.h"

void Offsets::GrabOffsets ()
{
	Utils::Offsets.m_iHealth = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_iHealth");
	Utils::Offsets.m_iTeamNum = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_iTeamNum");
	Utils::Offsets.m_bDormant = 0xE9;
	Utils::Offsets.m_bGunGameImmunity = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_bGunGameImmunity");
	Utils::Offsets.m_lifeState = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_lifeState");
	Utils::Offsets.m_fFlags = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_fFlags");
	Utils::Offsets.m_Local = Utils::NetVarManager->GetOffset ("DT_BasePlayer", "m_Local");
	Utils::Offsets.m_nTickBase = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_nTickBase");
	Utils::Offsets.m_nForceBone = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_nForceBone");
	Utils::Offsets.m_mBoneMatrix = Utils::Offsets.m_nForceBone + 0x1C;
	Utils::Offsets.m_viewPunchAngle = Utils::NetVarManager->GetOffset ("DT_BasePlayer", "m_Local") + 0x64;
	Utils::Offsets.m_aimPunchAngle = Utils::NetVarManager->GetOffset ("DT_BasePlayer", "m_Local") + 0x70;
	Utils::Offsets.m_vecOrigin = Utils::NetVarManager->GetOffset ("DT_BasePlayer", "m_vecOrigin");
	Utils::Offsets.m_vecViewOffset = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_vecViewOffset[0]");
	Utils::Offsets.m_vecVelocity = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_vecVelocity[0]");
	Utils::Offsets.m_szLastPlaceName = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_szLastPlaceName");
	Utils::Offsets.m_hActiveWeapon = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_hActiveWeapon");
	Utils::Offsets.m_fAccuracyPenalty = Utils::NetVarManager->GetOffset ("DT_WeaponCSBase", "m_fAccuracyPenalty");
	Utils::Offsets.m_Collision = Utils::NetVarManager->GetOffset ("DT_BasePlayer", "m_Collision");
	Utils::Offsets.m_iShotsFired = Utils::NetVarManager->GetOffset ("DT_CSPlayer", "m_iShotsFired");
	Utils::Offsets.m_iWeaponID = Utils::NetVarManager->GetOffset ("DT_WeaponCSBase", "m_fAccuracyPenalty") + 0x2C;
	Utils::Offsets.m_nMoveType = 0x258;

	Utils::Offsets.m_flNextPrimaryAttack = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	Utils::Offsets.m_nFallbackPaintKit = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_nFallbackPaintKit");
	Utils::Offsets.m_nFallbackSeed = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_nFallbackSeed");
	Utils::Offsets.m_flFallbackWear = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_flFallbackWear");
	Utils::Offsets.m_nFallbackStatTrak = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_nFallbackStatTrak");
	Utils::Offsets.m_AttributeManager = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_AttributeManager");
	Utils::Offsets.m_Item = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_Item");
	Utils::Offsets.m_iEntityLevel = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_iEntityLevel");
	Utils::Offsets.m_iItemIDHigh = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_iItemIDHigh");
	Utils::Offsets.m_iItemIDLow = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_iItemIDLow");
	Utils::Offsets.m_iAccountID = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_iAccountID");
	Utils::Offsets.m_iEntityQuality = Utils::NetVarManager->GetOffset ("DT_BaseCombatWeapon", "m_iEntityQuality");
	Utils::Offsets.m_OriginalOwnerXuidLow = Utils::NetVarManager->GetOffset ("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	Utils::Offsets.m_OriginalOwnerXuidHigh = Utils::NetVarManager->GetOffset ("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	Utils::Offsets.m_iItemDefinitionIndex = Utils::NetVarManager->GetOffset ("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
}