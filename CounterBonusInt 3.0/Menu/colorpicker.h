#pragma once

#include "element.h"

namespace MenuElements
{
	class ColorPicker : public MenuElements::Element
	{
	protected:
		float min, max;
		char* title;
		Vector* value;
	public:
		ColorPicker()
		{
			title = "";
			min = 0.f;
			max = 1.f;
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

		void SetValue (Vector* value_)
		{
			value = value_;
		}

		Vector* GetValue ()
		{
			return value;
		}

		void SetMin(float min_)
		{
			min = min_;
		}

		void SetMax(float max_)
		{
			max = max_;
		}
	};
}