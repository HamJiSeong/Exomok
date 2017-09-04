#include "ConsoleManipulator.h"
#include "console.h"

HANDLE hSTD_OUTPUT_HANDLE = NULL;

void initialize() {
	if (hSTD_OUTPUT_HANDLE == NULL)	hSTD_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
}

void setPreferences() {
	// Change the window title:
	SetConsoleTitle(L"EXOMOK");
	
	con_init();
	// con_hideCursor();

	system("mode con: cols=130 lines=45");
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	SetConsoleCursorInfo(hSTD_OUTPUT_HANDLE, &ConsoleCursor);
	// SetConsoleDisplayMode(hSTD_OUTPUT_HANDLE, CONSOLE_FULLSCREEN, NULL);
}