#include "BGMLibrary.h"

MCI_OPEN_PARMS mciOpenStack[10];
MCI_PLAY_PARMS mciPlayStack[10];
MCIDEVICEID dwIDStack[10];
unsigned int size;

DWORD LoadAvi(LPCWSTR filename)
{
	/* BGM 정보 */
	mciOpenStack[size].lpstrDeviceType = L"avivideo";
	mciOpenStack[size].lpstrElementName = filename;
	return mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenStack[size]);
	dwIDStack[size] = mciOpenStack[size].wDeviceID;
	++size;	
}

DWORD LoadWav(LPCWSTR filename)
{
	/* BGM 정보 */
	mciOpenStack[size].lpstrDeviceType = L"waveaudio";
	mciOpenStack[size].lpstrElementName = filename;
	return mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenStack[size]);
	dwIDStack[size] = mciOpenStack[size].wDeviceID;
	++size;
}

DWORD LoadMp3(LPCWSTR filename)
{
	/* BGM 정보 */
	mciOpenStack[size].lpstrDeviceType = L"mpegvideo";
	mciOpenStack[size].lpstrElementName = filename;
	DWORD result = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenStack[size]);
	dwIDStack[size] = mciOpenStack[size].wDeviceID;
	++size;
	return result;
}

DWORD PlayRes(const unsigned int pos, const char repeat) {
	//MCI_NOTIFY : 기본, MCI_DGV_PLAY_REPEAT : 반복
	mciSendCommand(dwIDStack[pos], MCI_PLAY, repeat ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayStack[pos]);
}

DWORD ResumeRes(const unsigned int pos) {
	return mciSendCommand(dwIDStack[pos], MCI_RESUME, 0, NULL);
}

DWORD PauseRes(const unsigned int pos) {
	return mciSendCommand(dwIDStack[pos], MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayStack[pos]);
}

DWORD StopRes(const unsigned int pos) {
	return mciSendCommand(dwIDStack[pos], MCI_CLOSE, 0, NULL);
}
