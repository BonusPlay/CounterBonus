#include "Globals.h"

CGlobals* Globals = new CGlobals ();

float CGlobals::GetCurrentTime ()
{
	return Memory->Read<float> (Offsets->m_dwGlobalPointer + 0x10);
}

float CGlobals::GetFrameTime ()
{
	return Memory->Read<float> (Offsets->m_dwGlobalPointer + 0x14);
}

int CGlobals::GetMaxClients ()
{
	return Memory->Read<int> (Offsets->m_dwGlobalPointer + 0x18);
}

float CGlobals::GetIntervalPerTick ()
{
	return Memory->Read<float> (Offsets->m_dwGlobalPointer + 0x20);
}

float CGlobals::GetInterpolationAmount ()
{
	return Memory->Read<float> (Offsets->m_dwGlobalPointer + 0x24);
}