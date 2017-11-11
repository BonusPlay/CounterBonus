#include "Bhop.h"

void bhop ()
{
	
	if (GetAsyncKeyState (Settings->bhopKey) & 0x8000 && !localPlayer->air ())
	{
		Mem->WriteMem (Offsets->clientDll + Offsets->Jump, 5);
	}
	else if (GetAsyncKeyState (Settings->bhopKey) & 0x8000 && localPlayer->air ())
	{
		Mem->WriteMem (Offsets->clientDll + Offsets->Jump, 4);
		Mem->WriteMem (Offsets->clientDll + Offsets->Jump, 5);
		Mem->WriteMem (Offsets->clientDll + Offsets->Jump, 4);
	}
	else
	{
		Mem->WriteMem (Offsets->clientDll + Offsets->Jump, 4);
	}
}