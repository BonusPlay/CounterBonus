#pragma once

#include <Windows.h>

#include "Utils\Toolbox.h"
#include "Utils\VMT.h"
#include "Utils\Settings.h"

#include "Interfaces\Interfaces.h"

#include "Hooks\CreateMove.h"

#include "SDK\Console.h"

using namespace toolkit;

DWORD WINAPI Main (LPVOID params);
void makeLogo ();