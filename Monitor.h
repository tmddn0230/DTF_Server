#pragma once

#include <Windows.h>

class Monitor
{
protected:
	HANDLE d_mutex;
public:
	Monitor(void);
	Monitor(char* name);
	~Monitor(void);

	void On() const;
	void Off() const;
};