#pragma once

#include "element.h"

namespace MenuElements
{
	class Checkbox : public MenuElements::Element
	{
	protected:
		int size;
		char* title;
		bool* value;
	public:
		Checkbox()
		{
			size = 16;
			title = "";
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

		void SetValue(bool value_)
		{
			*value = value_;
		}

		bool GetValue()
		{
			return *value;
		}
	};
}