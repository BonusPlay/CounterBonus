#include <iostream>
#include <string>
#include <Windows.h>

#include "Utils\Console.h"
#include "Utils\Memory.h"
#include "Utils\Offsets.h"
#include "Utils\XOR.h"
#include "Utils\Toolbox.h"

#include "Game\Engine.h"
#include "Game\LocalPlayer.h"

//#include "Visuals\Menu.h"

#include "Cheats\Bhop.h"
#include "Cheats\Triggerbot.h"
#include "Cheats\Aimbot.h"

using namespace std;

int main ()
{
	CConsole* Console = new CConsole ();
	SetConsoleTitle (XOR ("CounterBonusExt 2.0"));

	cout << XOR ("Ready to rock and roll");
	/*
	localPlayer->getPlayer ();

	while (true)
	{
		bhop ();
		triggerbot ();
		aimbot2 ();

		Sleep (5);
	}
	*/

	system (XOR("pause"));
	delete Console;
	return 0;
}