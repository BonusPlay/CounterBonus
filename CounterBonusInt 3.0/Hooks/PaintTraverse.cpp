#include "PaintTraverse.h"

#include <string.h>
#include "..\Menu\menu.h"

PaintTraverseFn oPaintTraverse;

void __fastcall Hooks::paintTraverse (void* _this, void* _edx, unsigned int panel, bool forceRepaint, bool allowForce)
{
	oPaintTraverse (_this, _edx, panel, forceRepaint, allowForce);

	static unsigned int drawPanel;
	if (!drawPanel)
		if (strstr (I::VPanel->GetName (panel), "MatSystemTopPanel"))
			drawPanel = panel;

	if (panel != drawPanel)
		return;

	Menu->Paint ();
}