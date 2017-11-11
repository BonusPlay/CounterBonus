#include "Input.h"

POINT CInput::GetMousePos ()
{
	static POINT ptMouse;
	hwCSGO = FindWindowA ("Valve001", NULL);

	GetCursorPos (&ptMouse);
	ScreenToClient (hwCSGO, &ptMouse);

	int width, height;
	I::Engine->getScreenSize (width, height);

	ptMouse.x = Utils::Clamp (ptMouse.x, 1, width);
	ptMouse.y = Utils::Clamp (ptMouse.y, 1, height);

	return ptMouse;
}

void CInput::GetClicked ()
{
	if (GetAsyncKeyState (VK_LBUTTON) && Input->hwCSGO == GetActiveWindow ())
	{
		bClicked = false;
		bMouseD = true;
	}
	else if (bMouseD)
	{
		bClicked = true;
		bMouseD = false;
	}
	else if (bClicked)
	{
		bClicked = false;
	}
}

bool CInput::Holding (int iXStart, int iYStart, int iWidth, int iHeight)
{
	if (GetAsyncKeyState (VK_LBUTTON) && Input->hwCSGO == GetActiveWindow ())
		if (Hovering (iXStart, iYStart, iWidth, iHeight))
			return true;

	return false;
}

bool CInput::Hovering (int iXStart, int iYStart, int iWidth, int iHeight)
{
	POINT ptMouse = Input->GetMousePos ();

	if (ptMouse.x >= iXStart && iXStart + iWidth >= ptMouse.x)
		if (ptMouse.y >= iYStart && iYStart + iHeight >= ptMouse.y)
			return true;

	return false;
}

bool CInput::Clicked (int iXStart, int iYStart, int iWidth, int iHeight)
{
	if (bClicked)
		if (Hovering (iXStart, iYStart, iWidth, iHeight))
			return true;

	return false;
}

CInput* Input;