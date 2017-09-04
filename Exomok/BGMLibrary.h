#pragma comment(lib,"Winmm.lib")

#ifndef _INC_WINDOWS
#include <Windows.h>
#endif

#ifndef _INC_MMSYSTEM
#include <MMSystem.h>
#endif

#ifndef _INC_DIGITALV
#include "Digitalv.h"
#endif

DWORD LoadAvi(LPCWSTR filename);
DWORD LoadWav(LPCWSTR filename);
DWORD LoadMp3(LPCWSTR filename);
DWORD PlayRes(const unsigned int pos, const char repeat);
DWORD ResumeRes(const unsigned int pos);
DWORD PauseRes(const unsigned int pos);
DWORD StopRes(const unsigned int pos);