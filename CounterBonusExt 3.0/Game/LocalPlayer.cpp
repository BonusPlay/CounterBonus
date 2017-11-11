#include "LocalPlayer.h"

CLocalPlayer* LocalPlayer = new CLocalPlayer ();

DWORD CLocalPlayer::Base ()
{
	return Offsets->m_dwLocalPlayer;
}

int CLocalPlayer::Health ()
{
	return Memory->Read<int> (Base () + NetVars->m_iHealth);
}

int CLocalPlayer::Team ()
{
	return Memory->Read<int> (Base () + NetVars->m_iTeamNum);
}

int CLocalPlayer::CrosshairID ()
{
	return Memory->Read<int> (Base () + Offsets->m_iCrosshairID);
}

int CLocalPlayer::ActiveWeaponBase ()
{
	return Memory->Read<int> (Base () + NetVars->m_hActiveWeapon);
}

int CLocalPlayer::ShotsFired ()
{
	return Memory->Read<int> (Base () + NetVars->m_iShotsFired);
}

Vector3 CLocalPlayer::Position ()
{
	return Memory->Read<Vector3> (Base () + NetVars->m_vecOrigin);
}

Vector3 CLocalPlayer::Angles ()
{
	return Memory->Read<Vector3> (Memory->GetEngineBase () + NetVars->m_vecViewOffset);
}

void CLocalPlayer::Angles (Vector3 value)
{
	Memory->Write<Vector3> (Memory->GetEngineBase () + NetVars->m_vecViewOffset, value);
}

Vector3 CLocalPlayer::EyePos ()
{
	return Position () + Angles ();
}

Vector3 CLocalPlayer::Velocity ()
{
	return Memory->Read<Vector3> (Base () + NetVars->m_vecVelocity);
}

float CLocalPlayer::FlashDuration ()
{
	return Memory->Read<float> (Base () + NetVars->m_flFlashDuration);
}

BYTE CLocalPlayer::Flags ()
{
	return Memory->Read<BYTE> (Base () + NetVars->m_fFlags);
}

#pragma warning (disable:4800)

bool CLocalPlayer::OnGround ()
{
	return Flags () & FL_ONGROUND;
}

bool CLocalPlayer::Jumping ()
{
	return Flags () & IN_JUMP;
}

bool CLocalPlayer::Zoomed ()
{
	return Flags () & IN_ZOOM;
}

void CLocalPlayer::Jump ()
{
	Memory->Write<int> (Memory->GetClientBase() + Offsets->m_dwForceJump, 5);
}

void CLocalPlayer::unJump ()
{
	Memory->Write<int> (Memory->GetClientBase () + Offsets->m_dwForceJump, 4);
}