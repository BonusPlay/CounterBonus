#pragma once

#include "Hooks.hpp"

#include "Options.hpp"
#include "SourceEngine/SDK.hpp"
#include "Utils/XOR.hpp"
#include "ImGUI/DX9/imgui_impl_dx9.h"
#include "Game/EntityESP.hpp"
#include "Utils/Toolbox.hpp"

namespace Hooks
{
	namespace I
	{
		std::unique_ptr<VFTableHook>	g_pD3DDevice9Hook = nullptr;
		std::unique_ptr<VFTableHook>	g_pClientModeHook = nullptr;
		std::unique_ptr<VFTableHook>	g_pMatSurfaceHook = nullptr;

		std::unique_ptr<DrawManager>	g_pRenderer = nullptr;
	}

	EndScene_t		g_fnOriginalEndScene = nullptr;
	Reset_t			g_fnOriginalReset = nullptr;
	CreateMove_t	g_fnOriginalCreateMove = nullptr;
	PlaySound_t		g_fnOriginalPlaySound = nullptr;

	WNDPROC			g_pOldWindowProc = nullptr; //Old WNDPROC pointer
	HWND			g_hWindow = nullptr; //Handle to the CSGO window

	bool			vecPressedKeys[256] = {};
	bool			g_bWasInitialized = false;

	void Initialize()
	{
		/*
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);
		*/

		NetvarManager::getInstance()->CreateDatabase();
		NetvarManager::getInstance()->Dump("netvar_dump.txt");

		auto dwDevice = **(uint32_t**)(Toolbox::getInstance()->FindSignature(XorStr("shaderapidx9.dll"), XorStr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);

		I::g_pD3DDevice9Hook = std::make_unique<VFTableHook>((PPDWORD)dwDevice, true);
		I::g_pClientModeHook = std::make_unique<VFTableHook>((PPDWORD)SourceEngine::Interfaces::ClientMode(), true);
		I::g_pMatSurfaceHook = std::make_unique<VFTableHook>((PPDWORD)SourceEngine::Interfaces::MatSurface(), true);

		while (!(g_hWindow = FindWindowA(XorStr("Valve001"), NULL)))
			Sleep(200);

		//Replace the WindowProc with our own to capture user input
		if (g_hWindow)
			g_pOldWindowProc = (WNDPROC)SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)Hooked_WndProc);

		g_fnOriginalReset = I::g_pD3DDevice9Hook->Hook(16, Hooked_Reset);                            //Hooks IDirect3DDevice9::EndScene
		g_fnOriginalEndScene = I::g_pD3DDevice9Hook->Hook(42, Hooked_EndScene);                      //Hooks IDirect3DDevice9::Reset

		g_fnOriginalPlaySound = I::g_pMatSurfaceHook->Hook(82, (PlaySound_t)Hooked_PlaySound);       //Hooks ISurface::PlaySound
		g_fnOriginalCreateMove = I::g_pClientModeHook->Hook(24, (CreateMove_t)Hooked_CreateMove);    //Hooks IClientMode::CreateMove
	}

	void GUI_Init(IDirect3DDevice9* pDevice)
	{
		//Initializes the GUI and the renderer
		ImGui_ImplDX9_Init(g_hWindow, pDevice);
		I::g_pRenderer = std::make_unique<DrawManager>(pDevice);
		I::g_pRenderer->CreateObjects();
		g_bWasInitialized = true;
	}

	LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//Captures the keys states
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			vecPressedKeys[VK_LBUTTON] = true;
			break;
		case WM_LBUTTONUP:
			vecPressedKeys[VK_LBUTTON] = false;
			break;
		case WM_RBUTTONDOWN:
			vecPressedKeys[VK_RBUTTON] = true;
			break;
		case WM_RBUTTONUP:
			vecPressedKeys[VK_RBUTTON] = false;
			break;
		case WM_KEYDOWN:
			vecPressedKeys[wParam] = true;
			break;
		case WM_KEYUP:
			vecPressedKeys[wParam] = false;
			break;
		default: break;
		}

		static bool isDown = false;
		static bool isClicked = false;
		if (vecPressedKeys[VK_INSERT])
		{
			isClicked = false;
			isDown = true;
		}
		else if (!vecPressedKeys[VK_INSERT] && isDown)
		{
			isClicked = true;
			isDown = false;
		}
		else
		{
			isClicked = false;
			isDown = false;
		}

		if (isClicked)
		{
			Options::g_bMainWindowOpen = !Options::g_bMainWindowOpen;

			//Use cl_mouseenable convar to disable the mouse when the window is open 
			static auto cl_mouseenable = SourceEngine::Interfaces::CVar()->FindVar(XorStr("cl_mouseenable"));
			cl_mouseenable->SetValue(!Options::g_bMainWindowOpen);
		}

		//Processes the user input using ImGui_ImplDX9_WndProcHandler
		if (g_bWasInitialized && Options::g_bMainWindowOpen && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true; //Input was consumed, return

						 //Input was not consumed by the GUI, call original WindowProc to pass the input to the game
		return CallWindowProc(g_pOldWindowProc, hWnd, uMsg, wParam, lParam);
	}

	HRESULT __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{

		//Correctly handling Reset calls is very important if you have a DirectX hook.
		//IDirect3DDevice9::Reset is called when you minimize the game, Alt-Tab or change resolutions.
		//When it is called, the IDirect3DDevice9 is placed on "lost" state and many related resources are released
		//This means that we need to recreate our own resources when that happens. If we dont, we crash.

		//GUI wasnt initialized yet, just call Reset and return
		if (!g_bWasInitialized)
			return g_fnOriginalReset(pDevice, pPresentationParameters);

		//Device is on LOST state.

		ImGui_ImplDX9_InvalidateDeviceObjects(); //Invalidate GUI resources
		I::g_pRenderer->InvalidateObjects();

		//Call original Reset.
		auto hr = g_fnOriginalReset(pDevice, pPresentationParameters);

		I::g_pRenderer->CreateObjects();
		ImGui_ImplDX9_CreateDeviceObjects(); //Recreate GUI resources
		return hr;
	}

	HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice)
	{
		static SourceEngine::ConVar* convar;

		if (!g_bWasInitialized)
		{
			GUI_Init(pDevice);
			convar = SourceEngine::Interfaces::CVar()->FindVar("cl_mouseenable");
		}
		else
		{
			//We don't want ImGui to draw the cursor when the main window isnt open
			ImGui::GetIO().MouseDrawCursor = Options::g_bMainWindowOpen;

			//Begins a new ImGui frame.
			ImGui_ImplDX9_NewFrame();

			if (Options::g_bMainWindowOpen)
			{
				//Begin Main window code
				ImGui::Begin(XorStr("CounterBonusInt 4.0"), &Options::g_bMainWindowOpen, ImVec2(300, 250), 0.75f);
				{
					if(ImGui::CollapsingHeader(XorStr("Aim")))
					{
						ImGui::Checkbox(XorStr("Full RCS"), &Options::g_bRCSEnabled);
						ImGui::Checkbox(XorStr("X axis RCS"), &Options::g_bXRCSEnabled);
					}
					if (ImGui::CollapsingHeader(XorStr("Visuals")))
					{
						ImGui::Checkbox(XorStr("ESP Enabled"), &Options::g_bESPEnabled);
						ImGui::Checkbox(XorStr("Ally Hitboxes"), &Options::g_bESPAllyHitboxesEnabled);
						ImGui::Checkbox(XorStr("Ally Names"), &Options::g_bESPAllyNamesEnabled);
						ImGui::ColorEdit4(XorStr("Ally Color"), Options::g_bESPAllyColor);
						ImGui::Checkbox(XorStr("Enemy Hitboxes"), &Options::g_bESPEnemyHitboxesEnabled);
						ImGui::Checkbox(XorStr("Enemy Names"), &Options::g_bESPEnemyNamesEnabled);
						ImGui::ColorEdit4(XorStr("Enemy Color"), Options::g_bESPEnemyColor);
					}
					if (ImGui::CollapsingHeader(XorStr("Misc")))
					{
						ImGui::Checkbox(XorStr("Bunny Hop"), &Options::g_bBHopEnabled);
					}
				}

				ImGui::End(); //End main window

							  //You can add more windows here if you want, just follow the style above
							  //Begin(...) to start a new window, End() to finish it
							  //More about ImGui: https://github.com/ocornut/imgui
			}

			//Begins rendering
			I::g_pRenderer->BeginRendering();

			if (SourceEngine::Interfaces::Engine()->IsInGame() && Options::g_bESPEnabled)
			{
				//Iterate over the EntityList
				for (int i = 1; i < SourceEngine::Interfaces::Engine()->GetMaxClients(); i++)
				{
					//Skip the local player
					if (i == SourceEngine::Interfaces::Engine()->GetLocalPlayer())
						continue;

					//Gets the entity by index
					auto pEntity = static_cast<C_CSPlayer*>(SourceEngine::Interfaces::EntityList()->GetClientEntity(i));

					if (!pEntity)
						continue; //Null check

					if (!pEntity->IsAlive() || pEntity->IsDormant())
						continue; //Skip Dead and Dormant entities

																			   //We only want to iterate over players. Make sure the ClassID is correct
					if (pEntity->GetClientClass()->m_ClassID == SourceEngine::EClassIds::CCSPlayer)
					{
						EntityESP esp(pEntity);

						if (Options::g_bESPEnabled)
						{
							esp.RenderESP(*I::g_pRenderer);
							esp.RenderName(*I::g_pRenderer);
						}
					}

				}
			}

			//Renders the GUI
			ImGui::Render();

			//Ends the rendering
			I::g_pRenderer->EndRendering();

		}

		//Call original EndScene now
		return g_fnOriginalEndScene(pDevice);
	}

	void __stdcall Hooked_PlaySound(const char* szFileName)
	{
		//Call original PlaySound
		g_fnOriginalPlaySound(SourceEngine::Interfaces::MatSurface(), szFileName);

		/*
		//This is the beep sound that is played when we have found a game
		if (!strcmp(szFileName, "weapons/hegrenade/beep.wav"))
		{
			//This will flash the CSGO window on the taskbar
			//so we know a game was found (you cant hear the beep sometimes cause it auto-accepts too fast)
			FLASHWINFO fi;
			fi.cbSize = sizeof(FLASHWINFO);
			fi.hwnd = g_hWindow;
			fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
			fi.uCount = 0;
			fi.dwTimeout = 0;
			FlashWindowEx(&fi);
		}
		*/
	}

	bool __stdcall Hooked_CreateMove(float sample_input_frametime, SourceEngine::CUserCmd* pCmd)
	{
		//Call original CreateMove
		bool bRet = g_fnOriginalCreateMove(SourceEngine::Interfaces::ClientMode(), sample_input_frametime, pCmd);

		//Get the Local player pointer
		auto pLocal = C_CSPlayer::GetLocalPlayer();

		//BunnyHop
		if (Options::g_bBHopEnabled)
		{
			//If the player is pressing the JUMP button AND we are on not on ground
			if ((pCmd->buttons & IN_JUMP) && !(pLocal->GetFlags() & (int)SourceEngine::EntityFlags::FL_ONGROUND))
				pCmd->buttons &= ~IN_JUMP;
		}

		
		//RCS
		if (Options::g_bRCSEnabled)
		{
			auto punchAngles = *pLocal->AimPunch() * 2.0f;
			if (punchAngles.x != 0.0f || punchAngles.y != 0)
			{
				pCmd->viewangles -= punchAngles;
				if (!Toolbox::getInstance()->Clamp(pCmd->viewangles))
					abort(); //Failed to clamp angles!!1! ABOOOOOORT

				return false;
			}
		}
		
		return bRet;
	}
}