#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <vector>

#include "Console.h"

using namespace std;

enum SignatureType
{
	NORMAL = 0x0,
	READ = 0x1,
	SUBTRACT = 0x2
};

class cMemory
{
public:
	cMemory ();
	~cMemory ();
	bool Attach (const string& ProcessName);
	MODULEENTRY32 GetModule (const std::string& ModuleName);
	bool Clear ();
	void Print ();

	template <class T>
	T Read (DWORD dwAddress)
	{
		T value;
		ReadProcessMemory (hProcess, (LPVOID)dwAddress, &value, sizeof (T), NULL);
		return value;
	}

	template <class T>
	T ReadSize (DWORD dwAddress, size_t Size)
	{
		T value;
		ReadProcessMemory (hProcess, (LPVOID)dwAddress, &value, Size, NULL);
		return value;
	}

	template <class T>
	T* ReadArray (DWORD dwAddress, size_t ArraySize)
	{
		T* arr;
		if (!ReadProcessMemory (hProcess, (LPVOID)dwAddress, arr, sizeof (T)*ArraySize, NULL)) arr = nullptr;
		return arr;
	}

	void inline ReadCustom (DWORD dwAddress, LPVOID buffer, size_t bytesToRead)
	{
		ReadProcessMemory (hProcess, (LPVOID)dwAddress, buffer, bytesToRead, NULL);
	}

	template <class T>
	bool Write (DWORD dwAddress, T ValueToWrite)
	{
		return WriteProcessMemory (hProcess, (LPVOID)dwAddress, &ValueToWrite, sizeof (T), NULL) == TRUE;
	}

	template <class T>
	bool WriteSize (DWORD dwAddress, T ValueToWrite, size_t Size)
	{
		return WriteProcessMemory (hProcess, (LPVOID)dwAddress, &ValueToWrite, Size, NULL) == TRUE;
	}

	template <class T>
	bool WriteArray (DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
	{
		return WriteProcessMemory (hProcess, (LPVOID)dwAddress, ArrayToWrite, sizeof (T)*ArraySize, NULL) == TRUE;
	}

	void inline WriteCustom (DWORD dwAddress, LPVOID buffer, size_t bytesToWrite)
	{
		WriteProcessMemory (hProcess, (LPVOID)dwAddress, buffer, bytesToWrite, NULL);
	}

	template <class T>
	bool WriteProtected (DWORD dwAddress, T ValueToWrite)
	{
		DWORD_PTR oldprotect;
		if (!VirtualProtectEx (hProcess, (LPVOID)dwAddress, sizeof (T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
		if (!Write (dwAddress, ValueToWrite)) return false;
		if (!VirtualProtectEx (hProcess, (LPVOID)dwAddress, sizeof (T), oldprotect, NULL)) return false;
		return true;
	}

	template <class T>
	bool WriteProtectedSize (DWORD dwAddress, T ValueToWrite, size_t Size)
	{
		DWORD_PTR oldprotect;
		if (!VirtualProtectEx (hProcess, (LPVOID)dwAddress, sizeof (T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
		if (!WriteSize (dwAddress, ValueToWrite, Size)) return false;
		if (!VirtualProtectEx (hProcess, (LPVOID)dwAddress, sizeof (T), oldprotect, NULL)) return false;
		return true;
	}

	template <class T>
	bool WriteArrayProtected (DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
	{
		DWORD_PTR oldprotect;
		if (!VirtualProtectEx (hProcess, (LPVOID)dwAddress, sizeof (T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
		if (!WriteArray (dwAddress, ArrayToWrite, ArraySize)) return false;
		if (!VirtualProtectEx (hProcess, (LPVOID)dwAddress, sizeof (T), oldprotect, NULL)) return false;
		return true;
	}

	DWORD FindPattern (DWORD base, DWORD size, const char* pattern, short type, DWORD patternOffset, DWORD addressOffset);
	DWORD FindSignature (DWORD base, DWORD size, BYTE* sign, char* mask);

	HANDLE* GetProcHandle ()
	{
		return &this->hProcess;
	}

	DWORD GetProcID ()
	{
		return this->ProcessID;
	}

	string GetProcessName ()
	{
		return this->ProcessName;
	}

	MODULEENTRY32 GetClient ()
	{
		return this->ClientDll;
	}

	DWORD GetClientBase ()
	{
		return this->ClientBase;
	}

	DWORD GetClientSize ()
	{
		return this->ClientSize;
	}

	MODULEENTRY32 GetEngine ()
	{
		return this->EngineDll;
	}

	DWORD GetEngineBase ()
	{
		return this->EngineBase;
	}

	DWORD GetEngineSize () 
	{
		return this->EngineSize;
	}

private:
	HANDLE hProcess;
	DWORD ProcessID;
	string ProcessName;
	MODULEENTRY32 ClientDll;
	DWORD ClientBase;
	DWORD ClientSize;
	MODULEENTRY32 EngineDll;
	DWORD EngineBase;
	DWORD EngineSize;
};

extern cMemory* Memory;