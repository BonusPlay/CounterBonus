#include "Entity.h"

DWORD CEntity::Base ()
{
	return Memory->Read<DWORD> (Memory->GetClientBase () + Offsets->m_dwEntityList + (Index * 0x10));
}

DWORD CEntity::BoneBase ()
{
	return Memory->Read<DWORD> (Base () + NetVars->m_dwBoneMatrix);
}

int CEntity::Health ()
{
	return Memory->Read<int> (Base () + NetVars->m_iHealth);
}

int CEntity::Team ()
{
	return Memory->Read<int> (Base () + NetVars->m_iTeamNum);
}

int CEntity::ClassID ()
{
	return Memory->Read<int> (Memory->Read<int> (Memory->Read<int> (Memory->Read<int> (Base () + 0x8) + 2 * 0x4) + 0x1) + 20);
}

Vector3 CEntity::Position ()
{
	return Memory->Read<Vector3> (Base () + NetVars->m_vecOrigin);
}

Vector3 CEntity::BonePos (int id)
{
	Vector3 BonePos;
	BonePos.x = Memory->Read<float> (BoneBase () + 0x30 * id + 0x0C);
	BonePos.y = Memory->Read<float> (BoneBase () + 0x30 * id + 0x1C);
	BonePos.z = Memory->Read<float> (BoneBase () + 0x30 * id + 0x1C);
	return BonePos;
}

Vector3 CEntity::Velocity ()
{
	return Memory->Read<Vector3> (Base () + NetVars->m_vecVelocity);
}

bool CEntity::Spotted ()
{
	return Memory->Read<bool> (Base () + NetVars->m_bSpotted);
}

void CEntity::Spotted (bool value)
{
	Memory->Write<bool> (Base () + NetVars->m_bSpotted, value);
}

float CEntity::Distance ()
{
	return LocalPlayer->Position ().DistTo (Position ());
}

int CEntity::LifeState ()
{
	return Memory->Read<int> (Base () + NetVars->m_iLifeState);
}

BYTE CEntity::Flags ()
{
	return Memory->Read<BYTE> (Base () + NetVars->m_fFlags);
}

bool CEntity::OnGround ()
{
	return Flags () & FL_ONGROUND;
}

bool CEntity::Valid ()
{
	if (!Base ())
		return false;

	if (!BoneBase ())
		return false;

	if (Position ().IsZero ())
		return false;

	//if (Dormant ())
	//	return false;

	if (Team () == ETeams::Team_NoTeam || Team () != LocalPlayer->Team ())
		return false;

	if (LifeState () == LifeState::LIFE_DEAD || Health () <= 0)
		return false;

	return true;
}