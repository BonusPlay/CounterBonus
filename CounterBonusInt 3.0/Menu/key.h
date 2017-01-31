#pragma once

#include "element.h"

namespace MenuElements
{
	class Key : public MenuElements::Element
	{
	protected:
		bool waiting;
		char* title;
		int* value;
	public:
		Key()
		{
			title = "";
			waiting = false;
			value = NULL;
		}

		void Think();
		void Paint();

		void SetTitle(char* title_)
		{
			title = title_;
		}

		char* GetTitle()
		{
			return title;
		}

		void SetValue (int value_)
		{
			*value = value_;
		}

		int GetValue ()
		{
			return *value;
		}
	};
}

// this is stupid but i don't care.
char* szKeyNames[];