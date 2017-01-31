#pragma once

#include <vector>
#include <thread>

#include "Aimbot.h"
#include "Bhop.h"
#include "..\Utils\Console.h"
#include "..\Utils\Memory.h"
#include "..\Game\Offsets.h"
#include "..\Game\Netvars.h"
#include "..\Game\Enums.h"

extern std::vector<std::thread> threadPool;
extern bool bBhopThreadTerminate;
extern bool bBhopThreadStop;