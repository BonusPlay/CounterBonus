#pragma once

#include "..\Utils\Memory.h"

class COffsets
{
public:
	COffsets ();
	void Log ();

	DWORD m_dwLocalPlayer;
	DWORD m_dwEntityList;
	DWORD m_dwEnginePointer;
	DWORD m_dwForceAttack;
	DWORD m_dwForceJump;
	DWORD m_dwForward;
	DWORD m_dwViewAngles;
	DWORD m_iCrosshairID;
	DWORD m_dwGlowObject;
	DWORD m_dwViewMatrix;
	DWORD m_dwGlobalPointer;
	DWORD m_dwClientCMD;
	DWORD m_dwCInput;
	DWORD m_dwUserCMD;
	DWORD m_dwVerifiedCMD;
	DWORD m_dwNetvarClasses;
};

namespace Patterns
{
	extern BYTE pt_dwEntityList[];
	extern BYTE pt_dwLocalPlayer[];
	extern BYTE pt_dwEnginePointer[];
	extern BYTE pt_dwForceAttack[];
	extern BYTE pt_dwForceJump[];
	extern BYTE pt_iCrosshairID[];
	extern BYTE pt_dwViewMatrix[];
	extern BYTE pt_dwGlowObject[];
	extern BYTE pt_dwGlobalPointer[];
	extern BYTE pt_dwClientCMD[];
	extern BYTE pt_dwInput[];
	extern BYTE pt_dwNetVarClasses[];
}

namespace Masks
{
	extern char* msk_dwEntityList;
	extern char* msk_dwLocalPlayer;
	extern char* msk_dwEnginePointer;
	extern char* msk_dwForceAttack;
	extern char* msk_dwForceJump;
	extern char* msk_iCrosshairID;
	extern char* msk_dwViewMatrix;
	extern char* msk_dwGlowObject;
	extern char* msk_dwGlobalPointer;
	extern char* msk_dwClientCMD;
	extern char* msk_dwInput;
	extern char* msk_dwNetVarClasses;
}

extern COffsets* Offsets;