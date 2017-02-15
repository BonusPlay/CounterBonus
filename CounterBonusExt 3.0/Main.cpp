#include "Main.h"

int main (int argc, char** argv)
{
	if (!setup (argc, argv))
		cout << "FALSE";

	mainLoop ();
	cleanup ();

	return 0;
}

bool setup (int argc, char** argv)
{
	SetUnhandledExceptionFilter (unhandled_handler);
	Console = new cConsole ();

	MiscUtils = new CMiscUtils ();
	ThreadManager = new cThreadManager();

	Console->SetConsoleColor (dark_green, black);
	cout << "/==============================================================================\\"
		<< "|       ______                  __            ____                             |"
		<< "|      / ____/___  __  ______  / /____  _____/ __ )____  ____  __  _______     |"
		<< "|     / /   / __ \\/ / / / __ \\/ __/ _ \\/ ___/ __  / __ \\/ __ \\/ / / / ___/     |"
		<< "|    / /___/ /_/ / /_/ / / / / /_/  __/ /  / /_/ / /_/ / / / / /_/ (__  )      |"
		<< "|    \\____/\\____/\\__,_/_/ /_/\\__/\\___/_/  /_____/\\____/_/ /_/\\__,_/____/       |"
		<< "|                                                                              |"
		<< "|                        proudly presented by BonusPlay                        |"
		<< "|                                                                              |"
		<< "\\==============================================================================/" << endl;
	Console->SetConsoleColor (white, black);
	
	cout << "> Attempting to attatch to Counter-Strike: Global Offensive" << endl
		<< "If you haven't started CS:GO yet, please do it now" << endl;
	Memory = new cMemory ();
	Memory->Print ();

	cout << "================================================================================";
	cout << "> Grabbing offsets..." << endl;
	Offsets = new COffsets ();
	Offsets->Log ();
	
	cout << "================================================================================";
	cout << "> Grabbing nervars..." << endl;
	NetVars = new CNetVars ();
	NetVars->Log ();

	cout << "================================================================================";
	cout << "> Starting up threads..." << endl;

	ThreadManager->create("bhop", bhop);

	return true;
}

void mainLoop ()
{
	Console->Clear ();
	Console->SetConsoleColor (dark_green, black);
	cout << "/==============================================================================\\"
		<< "|       ______                  __            ____                             |"
		<< "|      / ____/___  __  ______  / /____  _____/ __ )____  ____  __  _______     |"
		<< "|     / /   / __ \\/ / / / __ \\/ __/ _ \\/ ___/ __  / __ \\/ __ \\/ / / / ___/     |"
		<< "|    / /___/ /_/ / /_/ / / / / /_/  __/ /  / /_/ / /_/ / / / / /_/ (__  )      |"
		<< "|    \\____/\\____/\\__,_/_/ /_/\\__/\\___/_/  /_____/\\____/_/ /_/\\__,_/____/       |"
		<< "|                                                                              |"
		<< "|                        proudly presented by BonusPlay                        |"
		<< "|                                                                              |"
		<< "\\==============================================================================/" << endl
		<< endl;
	Console->SetConsoleColor (white, black);

	int i;
	cin >> i;
}

void cleanup ()
{
	cout << "================================================================================";
	cout << "> Ending threads..." << endl;

	ThreadManager->endAll();

	delete MiscUtils;
	delete Memory;
	delete Offsets;
	delete NetVars;
	delete Console;
}