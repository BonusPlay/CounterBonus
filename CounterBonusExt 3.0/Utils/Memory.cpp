#include "Memory.h"

#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define getBits(x)		(INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte(x)		(getBits(x[0]) << 4 | getBits(x[1]))

typedef std::vector<unsigned char> vecByte;

CMemory* Memory;

CMemory::CMemory ()
{
	while (true)
	{
		if (Attach ("csgo.exe"))
		{
			ClientDll = GetModule ("client.dll");
			EngineDll = GetModule ("engine.dll");

			if (ClientDll.modBaseAddr == 0x0 || EngineDll.modBaseAddr == 0x0)
				continue;

			ClientBase = (DWORD)ClientDll.modBaseAddr;
			EngineBase = (DWORD)EngineDll.modBaseAddr;
			ClientSize = ClientDll.modBaseSize;
			EngineSize = EngineDll.modBaseSize;
			break;
		}

		cout << ".";
		Sleep (1000);
	}
}

CMemory::~CMemory ()
{
	Console->DebugMessage ("Memory shutting down");
}

bool CMemory::Attach (const std::string& ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, NULL);
	if (hPID == INVALID_HANDLE_VALUE) return false;
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof (procEntry);

	const WCHAR* procNameChar;
	int nChars = MultiByteToWideChar (CP_ACP, 0, ProcessName.c_str (), -1, NULL, 0);
	procNameChar = new WCHAR[ nChars ];
	MultiByteToWideChar (CP_ACP, 0, ProcessName.c_str (), -1, (LPWSTR)procNameChar, nChars);

	do
		if (!wcscmp (_bstr_t(procEntry.szExeFile), procNameChar))
		{
			this->ProcessID = procEntry.th32ProcessID;
			CloseHandle (hPID);
			this->hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, this->ProcessID);
			this->ProcessName = ProcessName;
			return true;
		}
	while (Process32Next (hPID, &procEntry));

	CloseHandle (hPID);
	return false;
}

MODULEENTRY32 CMemory::GetModule (const std::string& ModuleName)
{
	HANDLE hModule = CreateToolhelp32Snapshot (TH32CS_SNAPMODULE, ProcessID);
	MODULEENTRY32 mEntry;
	if (hModule == INVALID_HANDLE_VALUE)
	{
		mEntry.modBaseAddr = 0x0;
		return mEntry;
	}
	mEntry.dwSize = sizeof (mEntry);

	const WCHAR *modNameChar;
	int nChars = MultiByteToWideChar (CP_ACP, 0, ModuleName.c_str (), -1, NULL, 0);
	modNameChar = new WCHAR[ nChars ];
	MultiByteToWideChar (CP_ACP, 0, ModuleName.c_str (), -1, (LPWSTR)modNameChar, nChars);

	do
		if (!wcscmp (_bstr_t(mEntry.szModule), modNameChar))
		{
			CloseHandle (hModule);
			return mEntry;
		}
	while (Module32Next (hModule, &mEntry));

	CloseHandle (hModule);
	mEntry.modBaseAddr = 0x0;
	return mEntry;
}

bool CMemory::Clear ()
{
	return (CloseHandle (hProcess) == TRUE);
}

void CMemory::Print ()
{
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		cout << "You didn't attach to a process yet!" << std::endl;
		return;
	}

	Console->SuccessMessage ("[Memory] CS:GO attatched!");
	cout << "> hProcess = 0x" << hex << uppercase << hProcess << nouppercase << endl;
	cout << "> ProcessID = 0x" << hex << uppercase << ProcessID << nouppercase << endl;
	cout << "> ClientBase = 0x" << hex << uppercase << ClientBase << nouppercase << endl;
	cout << "> ClientSize = 0x" << hex << uppercase << ClientSize << nouppercase << endl;
	cout << "> EngineBase = 0x" << hex << uppercase << EngineBase << nouppercase << endl;
	cout << "> EngineSize = 0x" << hex << uppercase << EngineSize << nouppercase << endl;
}

DWORD CMemory::FindPattern (DWORD base, DWORD size, const char* pattern, short type, DWORD patternOffset, DWORD addressOffset)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	DWORD offset = 0;
	while (offset < size)
	{
		VirtualQueryEx (hProcess, (LPCVOID)(base + offset), &mbi, sizeof (MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE)
		{
			BYTE* buffer = new BYTE[ mbi.RegionSize ];
			ReadProcessMemory (hProcess, mbi.BaseAddress, buffer, mbi.RegionSize, NULL);
			for (unsigned int i = 0; i < mbi.RegionSize; i++)
			{
				if (DataCompare (buffer + i, pattern))
				{
					delete[] buffer;
					DWORD add = (DWORD)mbi.BaseAddress + i + patternOffset;

					if (type == SignatureType::SUBTRACT)
						add -= size;

					return add + addressOffset;
				}
			}

			delete[] buffer;
		}
		offset += mbi.RegionSize;
	}
	return 0;
}

bool DataCompare (const unsigned char* bytes, const char* pattern)
{
	for (; *pattern; *pattern != ' ' ? ++bytes : bytes, ++pattern)
	{
		if (*pattern == ' ' || *pattern == '?')
			continue;
		if (*bytes != getByte (pattern))
			return false;
		++pattern;
	}
	return true;
}

bool DataCompareOld (BYTE* data, BYTE* sign, char* mask)
{
	for (; *mask; mask++, sign++, data++)
	{
		if (*mask == 'x' && *data != *sign)
		{
			return false;
		}
	}
	return true;
}

DWORD CMemory::FindSignature (DWORD base, DWORD size, BYTE* sign, char* mask)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	DWORD offset = 0;
	while (offset < size)
	{
		VirtualQueryEx (hProcess, (LPCVOID)(base + offset), &mbi, sizeof (MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE)
		{
			BYTE* buffer = new BYTE[ mbi.RegionSize ];
			ReadProcessMemory (hProcess, mbi.BaseAddress, buffer, mbi.RegionSize, NULL);
			for (unsigned int i = 0; i < mbi.RegionSize; i++)
			{
				if (DataCompareOld (buffer + i, sign, mask))
				{
					delete[] buffer;
					return (DWORD)mbi.BaseAddress + i;
				}
			}

			delete[] buffer;
		}
		offset += mbi.RegionSize;
	}
	return 0;
}