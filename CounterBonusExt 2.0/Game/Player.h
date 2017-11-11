#pragma once

#include <Windows.h>

#include "Engine.h"

#include "..\Utils\Memory.h"
#include "..\Utils\Offsets.h"
#include "..\Utils\Vector.h"

class CPlayer
{
public:
	CPlayer ();
	~CPlayer ();

	DWORD player;

	void	getPlayer (int i);
	float*	getPos ();
	Vector	getVecPos ();
	float*	getEyePos ();
	Vector	getVelocity ();
	int		getHealth ();
	int		getTeam ();
	int		getFlags ();
	int		getGlowIndex ();
	int		getClassID ();
	bool	getAlive ();
	bool	isDead ();
	bool	isDormant ();
	DWORD	getClientClass ();
	DWORD	getBoneMatrix ();
	void	getBonePos (DWORD boneBase, int boneID, float * bonePos);
	void	vecGetBonePos (DWORD boneBase, int boneID, Vector &bonePos);
	float*	getHead ();
	float*	getBone (int bone);
	Vector	vecGetBone (int bone);
};

extern CPlayer* player;