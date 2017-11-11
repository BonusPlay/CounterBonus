#include "MiscUtils.h"

CMiscUtils* MiscUtils;

CMiscUtils::CMiscUtils ()
{
	Console->DebugMessage ("MiscUtils starting up");
}

CMiscUtils::~CMiscUtils ()
{
	Console->DebugMessage ("InputHelper shutting down");
}

std::string GenerateRandomString (int length)
{
	static const char alphanum[] =
		"0123456789"
		"!@#$%^&*"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	std::string str;

	for (int i = 0; i < length; i++)
	{
		str += alphanum[ rand () % sizeof (alphanum) - 1 ];
	}

	return str;
}

LONG WINAPI unhandled_handler (_EXCEPTION_POINTERS* e)
{
	MakeMinidump (e);
	return EXCEPTION_CONTINUE_SEARCH;
}

void MakeMinidump (_EXCEPTION_POINTERS *e)
{
	char dumpName[ MAX_PATH ];

	SYSTEMTIME t;
	GetSystemTime (&t);
	wsprintf (dumpName, "counterbonus_%4d%02d%02d_%02d%02d%02d.dmp", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);

	auto hFile = CreateFile (dumpName, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
		return;

	MINIDUMP_EXCEPTION_INFORMATION info;
	info.ThreadId = GetCurrentThreadId ();
	info.ExceptionPointers = e;
	info.ClientPointers = FALSE;

	char msg[ MAX_PATH ];

	if (MiniDumpWriteDump (GetCurrentProcess (), GetCurrentProcessId (), hFile, MiniDumpWithIndirectlyReferencedMemory, (e ? &info : nullptr), nullptr, nullptr))
	{
		sprintf (msg, "Crashdump created: '%s'\nPlease contact BonusPlay with this ASAP.", dumpName);
		MessageBox (NULL, msg, "Crash!", MB_OK);
	}
	else
	{
		sprintf (msg, "Unable to create crashdump!\nPlease contact BonusPlay with this:\n Error %d", GetLastError ());
		MessageBox (NULL, msg, "Crash!", MB_OK);
	}

	CloseHandle (hFile);
}