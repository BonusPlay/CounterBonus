#include "Console.h"

CConsole::CConsole ()
{
	SetConsoleCtrlHandler (CTRL_C_EVENT, TRUE);
	SetConsoleTitleA ("CounterBonusExt v.2.0");
	HANDLE ConInput = GetStdHandle (STD_INPUT_HANDLE);
	HANDLE ConOutput = GetStdHandle (STD_OUTPUT_HANDLE);
	freopen ("CON", "w", stdout);
	Console->SetConsoleCursor (false);
	this->ColorMessage (yellow, black, "> CounterBonusExt v.2.0 starting up\n");
}

CConsole::~CConsole ()
{
	exit (0);
}

int CConsole::GetWidth ()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int CConsole::GetHeight ()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void CConsole::Clear ()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hStdOut;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo (hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter (hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute (hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;
	SetConsoleCursorPosition (hStdOut, homeCoords);
}

void CConsole::SetConsoleCursor (bool cursor)
{
	CONSOLE_CURSOR_INFO curCursorInfo;
	curCursorInfo.bVisible = cursor;
	curCursorInfo.dwSize = 1;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &curCursorInfo);
}

void CConsole::SetConsoleColor (color textColor, color bgColor)
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void CConsole::SetConsoleSize (int width, int height)
{
	HWND hConsole = GetConsoleWindow ();
	RECT r;

	GetWindowRect (hConsole, &r);

	MoveWindow (hConsole, r.left, r.top, width, height, TRUE);
}

void CConsole::GotoXY (int x, int y)
{
	COORD CursorPosition = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), CursorPosition);
}

void CConsole::ColorMessage (color textColor, color bgColor, std::string msg)
{
	this->SetConsoleColor (textColor, bgColor);
	printf (msg.c_str());
	this->SetConsoleColor (green, black);
}