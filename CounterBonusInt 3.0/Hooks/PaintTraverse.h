#pragma once

typedef void (__fastcall *PaintTraverseFn)(void*, void*, unsigned int, bool, bool);
extern PaintTraverseFn oPaintTraverse;

namespace Hooks
{
	void __fastcall paintTraverse (void* _this, void* _edx, unsigned int panel, bool forceRepaint, bool allowForce);
}