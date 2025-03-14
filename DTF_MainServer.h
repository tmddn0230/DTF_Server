#pragma once

#include "resource.h"

void Init();

BOOL WinSockStart();

void Log(const char* format, ...);
void DebugLog(char* filename, const char* format, ...);

unsigned __stdcall ServerThread(void* pArg);
unsigned __stdcall UserThread(void* pArg);