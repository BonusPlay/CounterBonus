#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "Utils\Console.h"
#include "Utils\InputHelper.h"
#include "Utils\MiscUtils.h"
#include "Utils\Memory.h"

#include "Game\Offsets.h"
#include "Game\Netvars.h"

#include "Cheats\Cheats.h"

using namespace std;

bool setup (int argc, char** argv);
void mainLoop ();
void cleanup ();

#endif // MAIN_H