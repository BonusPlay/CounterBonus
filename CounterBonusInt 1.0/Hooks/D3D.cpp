#include "D3D.h"

CD3D::CD3D ()
{
	Direct3DCreate9Ex (D3D_SDK_VERSION, &this->Interface);
	if (Interface)
	{
		ZeroMemory (&this->Params, sizeof (this->Params));
		this->Params.Windowed = true;
		this->Params.Windowed = true;
		this->Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		this->Params.hDeviceWindow = OverlayWindow->Handle;
		this->Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		this->Params.BackBufferFormat = D3DFMT_A8R8G8B8;
		this->Params.BackBufferWidth = OverlayWindow->Width;
		this->Params.BackBufferHeight = OverlayWindow->Height;
		this->Params.EnableAutoDepthStencil = true;
		this->Params.AutoDepthStencilFormat = D3DFMT_D16;

		this->Interface->CreateDeviceEx (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, OverlayWindow->Handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &this->Params, 0, &this->Device);
		if (this->Device)
		{
			D3DXCreateLine (this->Device, &this->Line);
			if (this->Line)
			{
				this->Line->SetAntialias (true);
			}
			else
			{
				Console->ErrorMessage ("D3DXCreateLine failed!");
				return;
			}

			D3DXCreateFont (this->Device, 18, NULL, FW_NORMAL, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Calibri", &this->Font);
			if (this->Font)
			{
				this->Line->SetAntialias (true);
				return;	// SUCCESS
			}
			else
			{
				Console->ErrorMessage ("D3DXCreateFont failed!");
				return;
			}
		}
		else
		{
			Console->ErrorMessage ("CreateDeviceEx failed!");
			return;
		}
	}
	else
	{
		Console->ErrorMessage ("Direct3DCreate9Ex failed!");
		return;
	}
}

CD3D::~CD3D ()
{
	this->Line->Release ();
	this->Font->Release ();
	this->Device->Release ();
	this->Interface->Release ();
}

void CD3D::BeginRender ()
{
	this->Device->Clear (NULL, NULL, D3DCLEAR_TARGET, NULL, 1, NULL);
	this->Device->BeginScene ();
}

void CD3D::EndRender ()
{
	this->Device->EndScene ();
	this->Device->PresentEx (NULL, NULL, NULL, NULL, NULL);
}

void CD3D::DrawLine (float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[ 2 ];
	Points[ 0 ] = D3DXVECTOR2 (X, Y);
	Points[ 1 ] = D3DXVECTOR2 (XX, YY);
	if (Outlined)
	{
		this->Line->SetWidth (OutlineWidth * 2.f + LineWidth);
		this->Line->Draw (Points, 2, OutlineColor);
	}
	this->Line->SetWidth (LineWidth);
	this->Line->Draw (Points, 2, LineColor);
}

void CD3D::DrawCircle (float X, float Y, float Radius, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[ 50 ];
	for (int i = 0; i < 50; i++)
		Points[ i ] = D3DXVECTOR2 (X + (Radius * cos (i)), Y + (Radius * sin (i)));
	
	if (Outlined)
	{
		this->Line->SetWidth (LineWidth + OutlineWidth * 2);
		this->Line->Draw (Points, 50, OutlineColor);
	}
	this->Line->SetWidth (LineWidth);
	this->Line->Draw (Points, 50, LineColor);
}


void CD3D::DrawRect (float X, float Y, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	if (Filled)
	{
		if (Outlined)
			DrawLine (X - OutlineWidth, Y + Height / 2, X + Width + OutlineWidth, Y + Height / 2.f, Height, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine (X, Y + Height / 2.f, X + Width, Y + Height / 2, Height, LineColor, false, 0, 0);
	}
	else
	{
		if (Outlined)
		{
			OutlineWidth *= 2.f + LineWidth;
			DrawLine (X, Y, X, Y + Height, OutlineWidth, OutlineColor, false, 0, 0);
			DrawLine (X, Y + Height, X + Width, Y + Height, OutlineWidth, OutlineColor, false, 0, 0);
			DrawLine (X + Width, Y + Height, X + Width, Y, OutlineWidth, OutlineColor, false, 0, 0);
			DrawLine (X + Width, Y, X, Y, OutlineWidth, OutlineColor, false, 0, 0);
			DrawLine (X, Y, X, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine (X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine (X + Width, Y + Height, X + Width, Y, LineWidth, LineColor, false, 0, 0);
			DrawLine (X + Width, Y, X, Y, LineWidth, LineColor, false, 0, 0);
		}
		else
		{
			DrawLine (X, Y, X, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine (X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine (X + Width, Y + Height, X + Width, Y, LineWidth, LineColor, false, 0, 0);
			DrawLine (X + Width, Y, X, Y, LineWidth, LineColor, false, 0, 0);
		}
	}
}

void CD3D::DrawString (float X, float Y, std::wstring Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered)
{
	RECT Rect;
	Rect.top = Y;
	Rect.left = X;
	Rect.bottom = Y;
	Rect.right = X;
	if (Outlined)
	{
		RECT OutlineRectTop;
		OutlineRectTop.top = Y - 1.f;
		OutlineRectTop.left = X;
		OutlineRectTop.bottom = Y;
		OutlineRectTop.right = X - 1.f;
		RECT OutlineRectLeft;
		OutlineRectLeft.top = Y;
		OutlineRectLeft.left = X - 1.f;
		OutlineRectLeft.bottom = Y;
		OutlineRectLeft.right = X - 1.f;
		RECT OutlineRectRight;
		OutlineRectRight.top = Y;
		OutlineRectRight.left = X + 1.f;
		OutlineRectRight.bottom = Y;
		OutlineRectRight.right = X + 1.f;
		RECT OutlineRectBottom;
		OutlineRectBottom.top = Y + 1.f;
		OutlineRectBottom.left = X;
		OutlineRectBottom.bottom = Y + 1.f;
		OutlineRectBottom.right = X;
		if (Centered)
		{
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectTop, DT_CENTER | DT_NOCLIP, OutlineColor);
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectLeft, DT_CENTER | DT_NOCLIP, OutlineColor);
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectRight, DT_CENTER | DT_NOCLIP, OutlineColor);
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectBottom, DT_CENTER | DT_NOCLIP, OutlineColor);
		}
		else
		{
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectTop, DT_NOCLIP, OutlineColor);
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectLeft, DT_NOCLIP, OutlineColor);
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectRight, DT_NOCLIP, OutlineColor);
			this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &OutlineRectBottom, DT_NOCLIP, OutlineColor);
		}
	}

	if (Centered)
		this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &Rect, DT_CENTER | DT_NOCLIP, TextColor);
	else
		this->Font->DrawTextW (NULL, Text.c_str (), wcslen (Text.c_str ()), &Rect, DT_NOCLIP, TextColor);
}

void CD3D::DrawCross (float X, float Y, float Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	if (Outlined)
	{
		DrawLine (X - Size / 2.f - OutlineWidth, Y, X - 1.f, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine (X + Size / 2.f + OutlineWidth, Y, X, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine (X, Y - Size / 2.f - OutlineWidth, X, Y - 1.f, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine (X, Y + Size / 2.f + OutlineWidth, X, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
	}
	DrawLine (X - Size / 2.f, Y, X - 1.f, Y, LineWidth, CrossColor, false, OutlineWidth, OutlineColor);
	DrawLine (X + Size / 2.f, Y, X, Y, LineWidth, CrossColor, false, OutlineWidth, OutlineColor);
	DrawLine (X, Y - Size / 2.f, X, Y - 1.f, LineWidth, CrossColor, false, OutlineWidth, OutlineColor);
	DrawLine (X, Y + Size / 2.f, X, Y, LineWidth, CrossColor, false, OutlineWidth, OutlineColor);
}