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
	Console = new CConsole ();

	if (argc > 1)
		if (!strcmp (argv[ 1 ], "-debug"))
			Console->debug = true;

	MiscUtils = new CMiscUtils ();

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
	Memory = new CMemory ();
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

	//threadPool.emplace_back (&CBhop::Start, CBhop ());

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
}

void cleanup ()
{
	bBhopThreadStop = true;
	bBhopThreadTerminate = true;

	cout << "================================================================================";
	cout << "> Ending threads..." << endl;

	for (unsigned int i = 0; i < threadPool.size (); i++)
	{
		while (threadPool[ i ].joinable ())
		{
			cout << ".";
			threadPool[ i ].join ();
			Sleep (10);
			cout << endl << "Thread " << i << " ended!" << endl;
		}
	}

	delete MiscUtils;
	delete Memory;
	delete Offsets;
	delete NetVars;
	delete Console;
}