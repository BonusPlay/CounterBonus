#include "Offsets.h"

COffsets* Offsets;

COffsets::COffsets ()
{
	Console->DebugMessage ("OffsetHelper starting up");

	DWORD start;
	DWORD p1;
	DWORD p2;

	// ENTITY LIST
	//m_dwEntityList = Memory->FindPattern (Memory->GetClientBase (), Memory->GetClientSize (), "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", SignatureType::READ | SignatureType::SUBTRACT, 0x1, 0x0);
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwEntityList, Masks::msk_dwEntityList);
	p1 = Memory->Read<DWORD> (start + 0x1);
	p2 = Memory->Read<BYTE> (start + 0x7);
	m_dwEntityList = (p1 + p2) - Memory->GetClientBase ();

	// LOCAL PLAYER
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwLocalPlayer, Masks::msk_dwLocalPlayer);
	p1 = Memory->Read<DWORD> (start + 0x3);
	p2 = Memory->Read<BYTE> (start + 0x12);
	m_dwLocalPlayer = (p1 + p2) - Memory->GetClientBase ();
	
	// ENGINE POINTER + VIEW ANGLES
	start = Memory->FindSignature (Memory->GetEngineBase (), Memory->GetEngineSize (), Patterns::pt_dwEnginePointer, Masks::msk_dwEnginePointer);
	m_dwEnginePointer = Memory->Read<DWORD> (start + 0x16) - Memory->GetEngineBase ();
	m_dwViewAngles = Memory->Read<DWORD> (start + 0x1E);

	// FORCE ATTACK
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwForceAttack, Masks::msk_dwForceAttack);
	m_dwForceAttack = Memory->Read<DWORD> (start + 0x2);

	// FORCEJUMP + FORWARD
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwForceJump, Masks::msk_dwForceJump);
	m_dwForceJump = Memory->Read<DWORD> (start + 0x2) - Memory->GetClientBase();
	m_dwForward = Memory->Read<DWORD> (start + 0x8) - Memory->GetClientBase ();

	// CROSSHAIR ID
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_iCrosshairID, Masks::msk_iCrosshairID);
	m_iCrosshairID = Memory->Read<DWORD> (start + 0x6);

	// GLOW OBJECT
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwGlowObject, Masks::msk_dwGlowObject);
	m_dwGlowObject = Memory->Read<DWORD> (start + 0x58) - Memory->GetClientBase ();

	// VIEW MATRIX
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwViewMatrix, Masks::msk_dwViewMatrix);
	//p1 = Memory->Read<DWORD> (start + 0x4EE);
	p1 = Memory->Read<DWORD> (start + 0x502);
	m_dwViewMatrix = (p1 + 0x80) - Memory->GetClientBase ();

	// GLOBAL POINTER
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwGlobalPointer, Masks::msk_dwGlobalPointer);
	m_dwGlobalPointer = Memory->Read<DWORD> (start + 0x1);

	// CLIENTCMD
	start = Memory->FindSignature (Memory->GetEngineBase (), Memory->GetEngineSize (), Patterns::pt_dwClientCMD, Masks::msk_dwClientCMD);
	m_dwClientCMD = Memory->Read<DWORD> (start);

	// CINPUT + USERCMD + VERIFIEDCMD
	start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwInput, Masks::msk_dwInput);
	m_dwCInput = Memory->Read<DWORD>(start);
	m_dwUserCMD = Memory->Read<DWORD> (start + 0xEC);
	m_dwVerifiedCMD = Memory->Read<DWORD> (start + 0xF0);

	// NETVAR CLASSES
	start = Memory->FindSignature (Memory->GetClientBase (), 0xFFFFFF, (BYTE*)"DT_TEWorldDecal", "xxxxxxxxxxxxxxx");
	m_dwNetvarClasses = Memory->Read<DWORD> (Memory->FindSignature (Memory->GetClientBase (), 0xFFFFFF, (BYTE*)&start, "xxxx") + 0x2B);
	//start = Memory->FindSignature (Memory->GetClientBase (), Memory->GetClientSize (), Patterns::pt_dwNetVarClasses, Masks::msk_dwNetVarClasses);
	//m_dwNetvarClasses = Memory->Read<DWORD> (start);
}

void COffsets::Log ()
{
	Console->SuccessMessage ("[Offset Manager] Offsets:");
	cout << "> m_dwEntityList           = 0x" << hex << uppercase << m_dwEntityList << nouppercase << endl;
	cout << "> m_dwLocalPlayer          = 0x" << hex << uppercase << m_dwLocalPlayer << nouppercase << endl;
	cout << "> m_dwEnginePointer        = 0x" << hex << uppercase << m_dwEnginePointer << nouppercase << endl;
	cout << "> m_dwForceAttack          = 0x" << hex << uppercase << m_dwForceAttack << nouppercase << endl;
	cout << "> m_dwForceJump            = 0x" << hex << uppercase << m_dwForceJump << nouppercase << endl;
	cout << "> m_dwViewAngles           = 0x" << hex << uppercase << m_dwViewAngles << nouppercase << endl;
	cout << "> m_iCrosshairID           = 0x" << hex << uppercase << m_iCrosshairID << nouppercase << endl;
	cout << "> m_dwGlowObject           = 0x" << hex << uppercase << m_dwGlowObject << nouppercase << endl;
	cout << "> m_dwViewMatrix           = 0x" << hex << uppercase << m_dwViewMatrix << nouppercase << endl;
	cout << "> m_dwGlobalPointer        = 0x" << hex << uppercase << m_dwGlobalPointer << nouppercase << endl;
	cout << "> m_dwClientCMD            = 0x" << hex << uppercase << m_dwClientCMD << nouppercase << endl;
	cout << "> m_dwCInput               = 0x" << hex << uppercase << m_dwCInput << nouppercase << endl;
	cout << "> m_dwUserCMD              = 0x" << hex << uppercase << m_dwUserCMD << nouppercase << endl;
	cout << "> m_dwVerifiedCMD          = 0x" << hex << uppercase << m_dwVerifiedCMD << nouppercase << endl;
	cout << "> m_dwNetvarClasses        = 0x" << hex << uppercase << m_dwNetvarClasses << nouppercase << endl;
}

namespace Patterns
{
	BYTE pt_dwEntityList[] = { 0x05, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xE9, 0x00, 0x39, 0x48, 0x04 };
	BYTE pt_dwLocalPlayer[] = { 0x8D, 0x34, 0x85, 0x00, 0x00, 0x00, 0x00, 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x41, 0x08, 0x8B, 0x48, 0x00 };
	BYTE pt_dwEnginePointer[] = { 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x10, 0x15, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x2F, 0xD0, 0x76, 0x04, 0xF3, 0x0F, 0x58, 0xC1, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x80, 0x00, 0x00, 0x00, 0x00, 0xD9, 0x46, 0x04 };
	BYTE pt_dwForceAttack[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x04, 0xA8, 0x04, 0xBF };
	//BYTE pt_dwForceJump[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x08, 0xA8, 0x08, 0xBF };
	BYTE pt_dwForceJump[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x08 };
	BYTE pt_iCrosshairID[] = { 0x56, 0x57, 0x8B, 0xF9, 0xC7, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x81, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x75, 0x07, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x07 };
	BYTE pt_dwViewMatrix[] = { 0x53, 0x8B, 0xDC, 0x83, 0xEC, 0x08, 0x83, 0xE4, 0xF0, 0x83, 0xC4, 0x04, 0x55, 0x8B, 0x6B, 0x04, 0x89, 0x6C, 0x24, 0x04, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x98, 0x03, 0x00, 0x00 };
	BYTE pt_dwGlowObject[] = { 0x8D, 0x8F, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x89, 0x35, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x51 };
	BYTE pt_dwGlobalPointer[] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x10, 0x40, 0x10 };
	BYTE pt_dwClientCMD[] = { 0x55, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x80, 0xB8 };
	BYTE pt_dwInput[] = { 0xB9, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x75, 0x08, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x06 };
	BYTE pt_dwNetVarClasses[] = { 0x44, 0x54, 0x5F, 0x54, 0x45, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x44, 0x65, 0x63, 0x61, 0x6C };
}

namespace Masks
{
	char* msk_dwEntityList = "x????xx?xxx";
	char* msk_dwLocalPlayer = "xxx????xx????xxxxx?";
	char* msk_dwEnginePointer = "xxxxxxxx????xxxxxxxxxx????xxxx????xxx";
	char* msk_dwForceAttack = "xx????xx????xxxxxxxx";
	//char* msk_dwForceJump = "xx????xx????xxxxxxxxxxxx";
	char* msk_dwForceJump = "xx????xx????xxxxxxxx";
	char* msk_iCrosshairID = "xxxxxx????????xx????xx????xxx????xx";
	char* msk_dwViewMatrix = "xxxxxxxxxxxxxxxxxxxxxxx????xxxxxx";
	char* msk_dwGlowObject = "xx????x????xxx????xx????xx";
	char* msk_dwGlobalPointer = "x????xxxxx";
	char* msk_dwClientCMD = "xxxx????xx????xx";
	char* msk_dwInput = "x????xxxx????xx";
	char* msk_dwNetVarClasses = "xxxxxxxxxxxxxxx";
}