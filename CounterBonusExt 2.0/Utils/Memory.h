#pragma once

#include <Windows.h>
#include <TlHelp32.h>

class CMemory
{
public:
	CMemory ();
	~CMemory ();
	HANDLE hProcess;

	template <class cData>
	cData ReadMem (DWORD address)
	{
		cData cRead;
		ReadProcessMemory (hProcess, (LPVOID)address, &cRead, sizeof (cData), NULL);
		return cRead;
	}

	template <class cData>
	cData WriteMem (DWORD dwAddress, cData write)
	{
		WriteProcessMemory (hProcess, (LPVOID)dwAddress, &write, sizeof (cData), NULL);
		return 0;
	}

	virtual void  Process (char* ProcessName);
	virtual DWORD Module (char* ModuleName);
	virtual DWORD ModuleSize (char* ModuleName);
	virtual DWORD FindSignature (DWORD base, DWORD size, BYTE* sign, char* mask);

private:
	DWORD PID;
	virtual bool  DataCompare (BYTE* data, BYTE* sign, char* mask);
};

extern CMemory* Mem;