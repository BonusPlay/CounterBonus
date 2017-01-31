#pragma once

#include <Windows.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <cstdint>

#include "..\Utils\Memory.h"
#include "..\Utils\Offsets.h"
#include "..\Utils\Settings.h"
#include "..\Utils\XOR.h"

using namespace std;

#define OFFSET(a,b) (((uint32_t)a)+((uint32_t)b))
#define DEREF(type,a,b) *(type*)OFFSET(a,b)

class CEngine
{
public:
	CEngine ();
	~CEngine ();

	void attack ();
	bool alive (int hp);
	void MakeVector (float *pfIn, float *pfOut);
	void CalcAngle (float *src, float *dst, float *angles);
	void calcang (float *src, float *dst, float *punch, float *angles);
	void clampAngles (float* angles);
	void smoothAngles (float* angles, float* out);
	bool WorldToScreen (float* from, float* to, RECT rc);

	float GetFOV (float *angle, float *src, float *dst);

private:
	void FindLocalPlayer ();
	void FindEntityList ();
	void FindAttack ();
	void FindJump ();
	void FindEnginePointer ();
	void FindViewAngles ();
	void FindCrosshairID ();
	void FindGlowObject ();
	void FindViewMatrix ();
};

class CCommandVar
{
private:
	void* m_pICVar = 0;
	static unsigned char table[];
	static uint32_t toHash (char* str);
public:
	CCommandVar (void* pICVar) : m_pICVar (pICVar)
	{}
	void* Find (char* str);
};

extern CEngine* engine;
extern CCommandVar* commandVar;