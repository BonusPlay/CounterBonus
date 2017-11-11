#include "LocalPlayer.h"

#pragma warning( disable : 4172)

CLocalPlayer* localPlayer = new CLocalPlayer ();

CLocalPlayer::CLocalPlayer ()
{}

CLocalPlayer::~CLocalPlayer ()
{
	local = NULL;
}

void CLocalPlayer::getPlayer ()
{
	local = Mem->ReadMem<uintptr_t> (Offsets->clientDll + Offsets->LocalPlayer);
}

float* CLocalPlayer::getPos ()
{
	float pos[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(local + Offsets->m_vecOrigin), &pos, sizeof (float) * 3, 0);
	return pos;
}

Vector CLocalPlayer::getVecPos ()
{
	return Mem->ReadMem<Vector> (local + Offsets->m_vecOrigin);
}

float* CLocalPlayer::getPunch ()
{
	float punch[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(local + Offsets->m_vecPunch), &punch, sizeof (float) * 3, 0);
	return punch;
}

Vector CLocalPlayer::getVecPunch ()
{
	return Mem->ReadMem<Vector> (local + Offsets->m_vecPunch);
}

Vector CLocalPlayer::getVecEyePos ()
{
	Vector eye;
	eye = Mem->ReadMem<Vector> (local + Offsets->m_vecViewOffset);
	eye[ 0 ] += getPos ()[ 0 ];
	eye[ 1 ] += getPos ()[ 1 ];
	eye[ 2 ] += getPos ()[ 2 ];
	return eye;
}

float* CLocalPlayer::getEyePos ()
{
	float eye[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(local + Offsets->m_vecViewOffset), &eye, sizeof (float) * 3, 0);
	eye[ 0 ] += getPos ()[ 0 ];
	eye[ 1 ] += getPos ()[ 1 ];
	eye[ 2 ] += getPos ()[ 2 ];
	return eye;
}

float* CLocalPlayer::getClearEyePos ()
{
	float eye[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(local + Offsets->m_vecViewOffset), &eye, sizeof (float) * 3, 0);
	return eye;
}

Vector CLocalPlayer::getVecClearEyePos ()
{
	return Mem->ReadMem<Vector> (local + Offsets->m_vecViewOffset);
}

Vector CLocalPlayer::getVelocity ()
{
	return Mem->ReadMem<Vector> (local + Offsets->m_vecVelocity);
}

int CLocalPlayer::getHealth ()
{
	return Mem->ReadMem<int> (local + Offsets->m_iHealth);
}

int CLocalPlayer::getTeam ()
{
	return Mem->ReadMem<int> (local + Offsets->m_iTeamNum);
}

int CLocalPlayer::getFlags ()
{
	return Mem->ReadMem<int> (local + Offsets->m_fFlags);
}

int CLocalPlayer::getCrossID ()
{
	return Mem->ReadMem<int> (local + Offsets->CrosshairID);
}

int CLocalPlayer::getShotsFired ()
{
	return Mem->ReadMem<int> (local + Offsets->m_iShotsFired);
}

DWORD CLocalPlayer::getHandleWeap ()
{
	return Mem->ReadMem<DWORD> (local + Offsets->m_hActiveWeapon);
}

int CLocalPlayer::getWeapEnt ()
{
	return getHandleWeap () & 0xFFF;
}

DWORD CLocalPlayer::getCurrentWeapon ()
{
	return Mem->ReadMem<DWORD> (Offsets->clientDll + Offsets->EntityList + (getWeapEnt () - 1) * 0x10);
}

int CLocalPlayer::getAmmo ()
{
	return Mem->ReadMem<int> (getCurrentWeapon () + Offsets->m_iClip1);
}

int CLocalPlayer::getWeaponId ()
{
	return Mem->ReadMem<int> (getCurrentWeapon () + Offsets->m_iItemDefinitionIndex);
}

DWORD CLocalPlayer::getEnginePointer ()
{
	return Mem->ReadMem<DWORD> (Offsets->engineDll + Offsets->ClientState);
}

QAngle CLocalPlayer::getAngles ()
{
	return Mem->ReadMem<QAngle> (getEnginePointer () + Offsets->ViewAngles);
}

float* CLocalPlayer::getFloatAngles ()
{
	float ang[ 3 ];
	ReadProcessMemory (Mem->hProcess, (PBYTE*)(getEnginePointer () + Offsets->ViewAngles), &ang, sizeof (float) * 3, 0);
	return ang;
}

Vector CLocalPlayer::getVecAngles ()
{
	return Mem->ReadMem<Vector> (getEnginePointer () + Offsets->ViewAngles);
}

void CLocalPlayer::setAngles (float *pfAngles)
{
	float fNewViewAngles[ 3 ];
	memcpy ((void*)fNewViewAngles, (void*)pfAngles, 12);
	if (getEnginePointer ())
	{
		WriteProcessMemory (Mem->hProcess, (PBYTE*)(getEnginePointer () + Offsets->ViewAngles), &fNewViewAngles, sizeof (float) * 3, 0);
	}
}

bool CLocalPlayer::isScoped ()
{
	return Mem->ReadMem<bool> (local + Offsets->m_bIsScoped);
}

bool CLocalPlayer::isNonRcsWeapon ()
{
	if (isWeaponPistol () || isWeaponSniper ())
		return false;

	return true;
}

bool CLocalPlayer::isNonAimWeapon ()
{
	if (isWeaponKnife () || isWeaponGrenade () || isWeaponBomb () || isWeaponTaser () || isWeaponShotgun ())
		return false;

	return true;
}

bool CLocalPlayer::air ()
{
	return getFlags () == 256 || getFlags () == 258 || getFlags () == 260 || getFlags () == 262;
}

bool CLocalPlayer::isWeaponPistol ()
{
	if (getWeaponId () == WEAPON_DEAGLE || getWeaponId () == WEAPON_ELITE || getWeaponId () == WEAPON_FIVESEVEN || getWeaponId () == WEAPON_GLOCK || getWeaponId () == WEAPON_HKP2000 || getWeaponId () == WEAPON_P250 || getWeaponId () == WEAPON_TEC9 || getWeaponId () == WEAPON_USP_SILENCER)
		return true;

	return false;
}

bool CLocalPlayer::isWeaponSniper ()
{
	if (getWeaponId () == WEAPON_AWP || getWeaponId () == WEAPON_G3SG1 || getWeaponId () == WEAPON_SCAR20 || getWeaponId () == WEAPON_SSG08)
		return true;

	return false;
}

bool CLocalPlayer::isWeaponKnife ()
{
	if (getWeaponId () == WEAPON_KNIFE || getWeaponId () == WEAPON_KNIFE_T || getWeaponId () == WEAPON_KNIFEGG)
		return true;

	return false;
}

bool CLocalPlayer::isWeaponGrenade ()
{
	if (getWeaponId () == WEAPON_FLASHBANG || getWeaponId () == WEAPON_HEGRENADE || getWeaponId () == WEAPON_SMOKEGRENADE || getWeaponId () == WEAPON_MOLOTOV || getWeaponId () == WEAPON_INCGRENADE || getWeaponId () == WEAPON_DECOY)
		return true;

	return false;
}

bool CLocalPlayer::isWeaponBomb ()
{
	if (getWeaponId () == WEAPON_C4)
		return true;

	return false;
}

bool CLocalPlayer::isWeaponTaser ()
{
	if (getWeaponId () == WEAPON_TASER)
		return true;

	return false;
}

bool CLocalPlayer::isWeaponShotgun ()
{
	if (getWeaponId () == WEAPON_NOVA || getWeaponId () == WEAPON_SAWEDOFF || getWeaponId () == WEAPON_XM1014 || getWeaponId () == WEAPON_MAG7)
		return true;

	return false;
}