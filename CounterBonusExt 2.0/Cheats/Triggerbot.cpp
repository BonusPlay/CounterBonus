#include "Triggerbot.h"

void triggerbot ()
{
	int crossId = localPlayer->getCrossID ();
	int playerNumber = crossId - 1;

	player->getPlayer (playerNumber);

	if (GetAsyncKeyState (Settings->triggerKey))
	{
		if (crossId <= 64 && crossId >= 0 && player->getTeam () != localPlayer->getTeam () && player->getHealth () >= 1)
		{
			engine->attack ();
		}
	}

	Sleep (5);
}