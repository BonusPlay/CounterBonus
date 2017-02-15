#pragma once

#include <memory>
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "SourceEngine/SDK.hpp"
#include "Utils/VFTableHook.hpp"
#include "Utils/DrawManager.hpp"

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hooks
{
	typedef long(__stdcall* EndScene_t)(IDirect3DDevice9* device);
	typedef long(__stdcall* Reset_t)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
	typedef bool(__thiscall* CreateMove_t)(SourceEngine::IClientMode*, float, SourceEngine::CUserCmd*);
	typedef void(__thiscall* PlaySound_t)(SourceEngine::ISurface*, const char*);

	void Initialize();
	LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice);
	void __stdcall Hooked_PlaySound(const char* szFileName);
	bool __stdcall Hooked_CreateMove(float sample_input_frametime, SourceEngine::CUserCmd* pCmd);
}