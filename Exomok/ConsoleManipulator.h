#ifndef _INC_CONSOLE_MANIPULATOR
#define _INC_CONSOLE_MANIPULATOR 1

#ifndef _INC_WINDOWS
#include <windows.h>
#endif

// ENUM
typedef enum { UP, DOWN, LEFT, RIGHT, ENTER, ENTER1, ENTER2, ETC, D, R, F, G, ESC } KEY;

void initialize();
void setPreferences();
#endif