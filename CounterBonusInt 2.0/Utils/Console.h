#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string>

#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)

enum color
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};

class CConsole
{
public:
	CConsole ();
	~CConsole ();
	int GetWidth ();
	int GetHeight ();
	void Clear ();
	void SetConsoleCursor (bool cursor);
	void SetConsoleColor (color textColor, color bgColor);
	void SetConsoleSize (int width, int height);
	void GotoXY (int x, int y);
	void ColorMessage (color textColor, color bgColor, std::string msg);
	//void CenterMessage (color textColor, color bgColor, std::string msg);
};

extern CConsole* Console;