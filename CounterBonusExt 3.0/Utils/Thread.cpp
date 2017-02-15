#pragma once

#include "Thread.h"
#include "Console.h"

cThreadManager* ThreadManager;

cThreadManager::cThreadManager()
{
	Console->DebugMessage("sThread Manager starting up");
}

cThreadManager::~cThreadManager()
{
	Console->DebugMessage("sThread Manager shutting down");
}


bool cThreadManager::create(char* threadName, void* funcPtr)
{
	HANDLE newThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)funcPtr, 0, 0, 0);
	if (!newThread)
	{
		Console->ErrorMessage("Could not create thread %s", threadName);
		return false;
	}
	Console->Message("Created thread %s", threadName);
	threadList.push_back(Thread(threadName, newThread, funcPtr));
	return true;
}

bool cThreadManager::end(char* threadName)
{
	for (auto m : threadList)
	{
		if (!_stricmp(threadName, m.name))
		{
			if (TerminateThread(m.threadHandle, 0))
			{
				Console->Message("Ended thread %s", m.name);
				return true;
			}
			else
			{
				Console->ErrorMessage("Could not end thread %s", m.name);
				return false;
			}
		}
	}
}

void cThreadManager::endAll()
{
	for (auto m : threadList)
		end(m.name);
}