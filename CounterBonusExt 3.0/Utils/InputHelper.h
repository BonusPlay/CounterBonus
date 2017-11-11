#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Console.h"

using namespace std;

class InputHelper
{
public:
	InputHelper (int &argc, char** argv);
	~InputHelper ();
	bool cmdOptionExists (string option);
	string cmdOptionValue (string option);

private:
	vector<string> options;
};