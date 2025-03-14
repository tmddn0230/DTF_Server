#include "Monitor.h"

Monitor::Monitor(void)
{
	//d_mutex = CreateMutex(NULL, false, NULL);
	//if (d_mutex == NULL)
	//	throw MessageBox(NULL, "Monitor() - Mutex creation failed.", NULL, MB_OK);

}
Monitor::Monitor(char* name)
{
	//d_mutex = CreateMutex(NULL, false, name);
	//if (d_mutex == NULL)
	//	throw MessageBox(NULL, "Monitor() - Mutex creation failed.", NULL, MB_OK);

}

Monitor::~Monitor(void)
{
	if (d_mutex != NULL)
	{
		CloseHandle(d_mutex);
		d_mutex = NULL;
	}
}

void Monitor::On() const
{
	WaitForSingleObject(d_mutex, INFINITE);
}

void Monitor::Off() const
{
	ReleaseMutex(d_mutex);
}