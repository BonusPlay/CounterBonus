#pragma once

#include "element.h"

namespace MenuElements
{
	class Frame : public MenuElements::Element
	{
	protected:

	public:
		Frame()
		{
			//ox = 4;
			//oy = 32;
			static CVar* mouselock = I::CVar->FindVar("cl_mouseenable");
			mouselock->SetValue(0);
			visible = true;
			I::InputSystem->EnableInput(false);
		}

		void Think();
		void Paint();
	};
}