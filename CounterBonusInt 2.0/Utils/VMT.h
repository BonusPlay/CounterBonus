#pragma once

#include <Windows.h>

#define k_page_writeable (PAGE_READWRITE | PAGE_EXECUTE_READWRITE)
#define k_page_readable (k_page_writeable|PAGE_READONLY|PAGE_WRITECOPY|PAGE_EXECUTE_READ|PAGE_EXECUTE_WRITECOPY)
#define k_page_offlimits (PAGE_GUARD|PAGE_NOACCESS)

class CVMT
{
public:
	template< typename Function > Function getvfunc (PVOID Base, DWORD Index)
	{

		PDWORD* VTablePointer = (PDWORD*)Base;
		PDWORD VTableFunctionBase = *VTablePointer;
		DWORD dwAddress = VTableFunctionBase[ Index ];
		return (Function)(dwAddress);
	}

	inline void* GetFunction (void* Instance, int Index)
	{
		DWORD VirtualFunction = (*(DWORD*)Instance) + sizeof (DWORD) * Index;
		return (void*)*((DWORD*)VirtualFunction);
	}

}; CVMT VMT;

class CVMTHookManager
{
public:
	CVMTHookManager ()
	{}

	~CVMTHookManager ()
	{
		this->HookTable (false);
	}

	CVMTHookManager (void* Interface)
	{
		this->Init (Interface);
	}

	bool Init (void* Interface)
	{
		pOrgTable = *(void**)Interface;
		this->count = this->GetCount ();
		pCopyTable = malloc (sizeof (void*)* count);
		memcpy (pCopyTable, pOrgTable, sizeof (void*) * count);
		pObject = (DWORD*)Interface;
		return true;
	}

	void HookTable (bool hooked)
	{
		if (hooked)
		{
			*pObject = (DWORD)pCopyTable;
		}
		else
		{
			*pObject = (DWORD)pOrgTable;
		}
	}

	void* HookFunction (int Index, void* hkFunction)
	{
		if (Index < this->count && Index >= 0)
		{
			((DWORD*)pCopyTable)[ Index ] = (DWORD)hkFunction;
			return (void*)((DWORD*)pOrgTable)[ Index ];
		}
		return NULL;
	}

private:
	bool CanReadPointer (void* table)
	{
		MEMORY_BASIC_INFORMATION mbi;
		if (table == nullptr) return false;
		if (!VirtualQuery (table, &mbi, sizeof (mbi))) return false;
		if (mbi.Protect & k_page_offlimits) return false;
		return (mbi.Protect & k_page_readable);
	}

	int GetCount ()
	{
		int index = 0;
		void** table = ((void**)pOrgTable);
		for (void* fn; (fn = table[ index ]) != nullptr; index++)
		{
			if (!this->CanReadPointer (fn)) break;
		}
		return index;
	}

	int count;
	void* pCopyTable;
	DWORD* pObject;
	void* pOrgTable;
};