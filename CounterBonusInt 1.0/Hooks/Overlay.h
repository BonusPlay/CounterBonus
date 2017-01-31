#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include <Windows.h>
#include <Uxtheme.h>

#include "..\Utils\Console.h"

class COverlayWindow
{
public:
	COverlayWindow ();
	~COverlayWindow ();

	HWND Handle;
	float Width;
	float Height;

	void Refresh ();
	static LRESULT CALLBACK WndProc (HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);

private:
	float X;
	float Y;
	MSG Message;
	WNDCLASSEX Class;
	RECT Bounds;

};

extern COverlayWindow* OverlayWindow;