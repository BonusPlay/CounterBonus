#include "Toolbox.h"

bool dataCompare (const char* base, const char* pattern)
{
	for (; *pattern; ++base, ++pattern)
		if (*pattern != '?' && *base != *pattern)
			return 0;

	return *pattern == 0;
}

DWORD Utils::findPattern (DWORD address, size_t size, const char* pattern)
{
	for (size_t i = 0; i < size; ++i, ++address)
		if (dataCompare ((const char*)address, pattern))
			return address;

	return 0;
}

uint64_t Utils::findSignature (const char* szModule, const char* szSignature)
{
	//CREDITS: learn_more
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

	MODULEINFO modInfo;
	GetModuleInformation (GetCurrentProcess (), GetModuleHandleA (szModule), &modInfo, sizeof (MODULEINFO));
	DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
	DWORD endAddress = startAddress + modInfo.SizeOfImage;
	const char* pat = szSignature;
	DWORD firstMatch = 0;
	for (DWORD pCur = startAddress; pCur < endAddress; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte (pat))
		{
			if (!firstMatch) firstMatch = pCur;
			if (!pat[ 2 ]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;    //one ?
		}
		else
		{
			pat = szSignature;
			firstMatch = 0;
		}
	}
	return NULL;
}