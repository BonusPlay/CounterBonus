#pragma once

#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <Psapi.h>
#include "Vector.h"

#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define RAD2DEG(x)	((float)(x) * (float)(180.f / M_PI))
#define DEG2RAD(x)	((float)(x) / (float)(180.f / M_PI))

typedef float matrix3x4_t[ 3 ][ 4 ];
typedef float matrix4x4_t[ 4 ][ 4 ];
typedef void* (*CreateInterfaceFn) (const char*, int*);

namespace Utils
{
	template<typename Ex>
	inline Ex getExport (const char *dll, const char *name)
	{
		return (Ex)((void *(*)(const char *, const char *))GetProcAddress (GetModuleHandleA (dll), name));
	}

	template<typename I>
	inline I createInterface (const char *dll, const char *name)
	{
		return (I)(((void *(*)(const char *, void *))GetProcAddress (GetModuleHandleA (dll), "CreateInterface"))(name, 0));
	}

	template<typename T>
	inline T readPtr (const void *base, int o)
	{
		return *(T *)((const char *)base + o);
	}

	template<typename T>
	inline void writePtr (void *base, int o, T v)
	{
		*(T *)((char *)base + o) = v;
	}

	template<typename T>
	inline T *makePtr (void *base, int o)
	{
		return (T *)((char *)base + o);
	}

	template<typename Fn>
	inline Fn getVFunc (const void *v, int i)
	{
		return (Fn)*(*(const void ***)v + i);
	}

	template <typename T>
	T* getInterface (const char* filename, const char* version)
	{
		void* library = dlopen (filename, RTLD_NOLOAD | RTLD_NOW);

		if (!library)
			return nullptr;

		void* createinterface_sym = dlsym (library, "CreateInterface");

		if (!createinterface_sym)
			return nullptr;

		CreateInterfaceFn factory = reinterpret_cast<CreateInterfaceFn>(createinterface_sym);

		return reinterpret_cast<T*>(factory (version, nullptr));
	}

	template <typename T>
	T* forceInterface (const char* filename, const char* version)
	{
		for (int i = 0; i < 100; i++)
		{
			char* versionString;
			//sprintf (&versionString, "%s%03d", version, i);

			if (getInterface<T> (filename, versionString))
				return getInterface<T> (filename, versionString);
		}
	}

	template< class T, class Y >
	T Clamp (T const &val, Y const &minVal, Y const &maxVal)
	{
		if (val < minVal)
			return minVal;
		else if (val > maxVal)
			return maxVal;
		else
			return val;
	}

	DWORD findPattern (DWORD address, size_t size, const char* pattern);
	uint64_t findSignature (const char* szModule, const char* szSignature);
}