#pragma once

#include "..\Utils\Console.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Overlay.h"

class CD3D
{
public:
	CD3D ();
	~CD3D ();

	void BeginRender ();
	void EndRender ();
	void DrawLine (float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawCircle (float X, float Y, float Radius, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawRect (float X, float Y, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawCross (float X, float Y, float Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawString (float X, float Y, std::wstring Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered);
private:
	IDirect3D9Ex* Interface;
	IDirect3DDevice9Ex* Device;
	D3DPRESENT_PARAMETERS Params;
	ID3DXLine* Line;
	ID3DXFont* Font;
};

extern CD3D* D3D;