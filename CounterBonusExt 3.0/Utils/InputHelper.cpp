#include "InputHelper.h"

InputHelper::InputHelper (int &argc, char** argv)
{
	Console->DebugMessage ("InputHelper starting up");

	for (int i = 1; i < argc; i++)
	{
		this->options.push_back (string (argv[ i ]));
	}
}

InputHelper::~InputHelper ()
{
	Console->DebugMessage ("InputHelper shutting down");
}

bool InputHelper::cmdOptionExists (string option)
{
	return find (this->options.begin (), this->options.end (), option) != this->options.end ();
}

string InputHelper::cmdOptionValue (string option)
{
	vector<string>::iterator itr = find (this->options.begin (), this->options.end (), option);
	if (itr != this->options.end () && ++itr != this->options.end ())
		return *itr;
	return "";
}