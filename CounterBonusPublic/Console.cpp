#pragma once
#include "Console.hpp"
#include <Windows.h>

#define GetArgs(from, to) va_list args; va_start(args, from); vsprintf_s(to, from, args); va_end(args);

cConsole* Console;

cConsole::cConsole()
{
	DWORD consoleMode;
	HANDLE ConInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE ConOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(ConInput, consoleMode);
	SetConsoleCtrlHandler(CTRL_C_EVENT, TRUE);
	freopen("CON", "w", stdout);
	SetConsoleTitle(GenerateRandomString(20).c_str());
	Console->SetConsoleCursor(false);
	Console->Clear();
	this->DebugMessage("ConsoleHandler starting up");
	this->SetConsoleColor(white, black);
}

cConsole::~cConsole()
{
	this->DebugMessage("ConsoleHandler shutting down");
	FreeConsole();
}

int cConsole::GetWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int cConsole::GetHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void cConsole::Clear()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hStdOut;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
		return;
	cellCount = csbi.dwSize.X*csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void cConsole::SetConsoleCursor(bool cursor)
{
	CONSOLE_CURSOR_INFO curCursorInfo;
	curCursorInfo.bVisible = cursor;
	curCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curCursorInfo);
}

void cConsole::SetConsoleColor(color textColor, color bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void cConsole::SetConsoleSize(int width, int height)
{
	HWND hConsole = GetConsoleWindow();
	RECT r;

	GetWindowRect(hConsole, &r);

	MoveWindow(hConsole, r.left, r.top, width, height, TRUE);
}

void cConsole::GotoXY(int x, int y)
{
	COORD CursorPosition = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void cConsole::Message(std::string msg)
{
	printf(msg.c_str());
	printf("\n");
}

void cConsole::Message(char* msg, ...)
{
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
}

void cConsole::RawMessage(std::string msg)
{
	printf(msg.c_str());
}

void cConsole::RawMessage(char* msg, ...)
{
	char buf[128];
	GetArgs(msg, buf);
	printf("%s", buf);
}

void cConsole::ColorMessage(color textColor, color bgColor, std::string msg)
{
	this->SetConsoleColor(textColor, bgColor);
	printf(msg.c_str());
	printf("\n");
	this->SetConsoleColor(white, black);
}

void cConsole::ColorMessage(color textColor, color bgColor, char* msg, ...)
{
	this->SetConsoleColor(textColor, bgColor);
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
	this->SetConsoleColor(white, black);
}

void cConsole::DebugMessage(std::string msg)
{
#if DEBUG
	this->ColorMessage(purple, black, "[DEBUG] " + msg);
#endif
}

void cConsole::DebugMessage(char* msg, ...)
{
#if DEBUG
	this->SetConsoleColor(purple, black);
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
	this->SetConsoleColor(white, black);
#endif
}

void cConsole::SuccessMessage(std::string msg)
{
	this->ColorMessage(dark_green, black, msg);
}

void cConsole::SuccessMessage(char* msg, ...)
{
	this->SetConsoleColor(green, black);
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
	this->SetConsoleColor(white, black);
}

void cConsole::ErrorMessage(std::string msg)
{
	this->ColorMessage(red, black, "[ERROR] " + msg);
}

void cConsole::ErrorMessage(char* msg, ...)
{
	this->SetConsoleColor(red, black);
	char buf[128];
	GetArgs(msg, buf);
	printf("[ERROR] %s\n", buf);
	this->SetConsoleColor(white, black);
}

std::string cConsole::GenerateRandomString(int length)
{
	static const char alphanum[] =
		"0123456789"
		"!@#$%^&*"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	std::string str;

	for (int i = 0; i < length; i++)
	{
		str += alphanum[rand() % sizeof(alphanum) - 1];
	}

	return str;
}