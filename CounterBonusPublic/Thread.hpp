#pragma once
#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include <vector>

struct sThread
{
	sThread(char* cname, HANDLE chandle, void* fPtr)
	{
		strcpy_s(name, cname);
		threadHandle = chandle;
		funcPtr = fPtr;
	}

	char name[64];
	HANDLE threadHandle;
	void* funcPtr;
};

class cThreadManager
{
public:
	cThreadManager();
	~cThreadManager();

	bool create(char* threadName, void* funcPtr);
	bool end(char* threadName);
	void endAll();

private:
	std::vector<sThread> threadList;
};

extern cThreadManager* Thread;

#endif // THREAD_H