#include "Overlay.h"

COverlayWindow::COverlayWindow ()
{
	ZeroMemory (&this->Class, sizeof (this->Class));
	this->Class.cbSize = sizeof (this->Class);
	this->Class.hInstance = GetModuleHandle (NULL);
	this->Class.lpfnWndProc = this->WndProc;
	std::wstring WindowName = L"CounterBonus";
	this->Class.lpszClassName = WindowName.c_str ();
	this->Class.style = CS_HREDRAW | CS_VREDRAW;
	this->Class.hbrBackground = CreateSolidBrush (RGB (0, 0, 0));
	if (RegisterClassEx (&this->Class))
	{
		this->Handle = CreateWindowEx (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, this->Class.lpszClassName, this->Class.lpszClassName, WS_POPUP, this->X, this->Y, this->Width, this->Height, NULL, NULL, this->Class.hInstance, NULL);
		if (this->Handle)
		{
			SetLayeredWindowAttributes (this->Handle, RGB (0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
			ShowWindow (this->Handle, 1);
			MARGINS Margin = { -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea (this->Handle, &Margin);
			HWND WinHandle = FindWindow (NULL, L"Counter Strike - Global Offensive"); // TODO
			if (WinHandle)
			{
				if (IsWindowVisible (WinHandle))
				{
					GetClientRect (WinHandle, &this->Bounds);
					this->Width = this->Bounds.right - this->Bounds.left;
					this->Height = this->Bounds.bottom - this->Bounds.top;
					ZeroMemory (&this->Bounds, sizeof (this->Bounds));
					GetWindowRect (WinHandle, &this->Bounds);
					this->X = this->Bounds.left;
					this->Y = this->Bounds.top;
					SetWindowPos (this->Handle, HWND_TOPMOST, this->X, this->Y, this->Width, this->Height, NULL);
					return;
				}
			}
		}
	}
	Console->ErrorMessage ("Overlay constructor");
	return;
}

COverlayWindow::~COverlayWindow ()
{
	DestroyWindow (this->Handle);
	UnregisterClass (this->Class.lpszClassName, this->Class.hInstance);
}

LRESULT CALLBACK COverlayWindow::WndProc (HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
	{
		// pESP.Functions.Tick (); TODO
	}
	case WM_ERASEBKGND:
	{
		return 0;
	}
	default:
	{
		return DefWindowProc (Handle, Message, wParam, lParam);
	}
	}
}

void COverlayWindow::Refresh ()
{
	InvalidateRect (this->Handle, NULL, false);
	if (PeekMessage (&this->Message, this->Handle, 0, 0, PM_REMOVE))
	{
		TranslateMessage (&this->Message);
		DispatchMessage (&this->Message);
	}
}