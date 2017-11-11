#pragma once

#include <Windows.h>
#include <DbgHelp.h>
#include <string>

#include "Console.h"

std::string GenerateRandomString (int length);
void MakeMinidump (_EXCEPTION_POINTERS *e);
LONG WINAPI unhandled_handler (_EXCEPTION_POINTERS* e);

class CMiscUtils
{
public:
	CMiscUtils ();
	~CMiscUtils ();
};

extern CMiscUtils* MiscUtils;