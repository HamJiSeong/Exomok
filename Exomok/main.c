#include "ConsoleManipulator.h"
#include "BoardControl.h"
#include "BGMLibrary.h"
#include "console.h"

int main() {
	initialize();
	setPreferences();
	extern char exitByUser;

 	showIntro();
	initBoard();

	while (1) {
		con_clearScr();
		showBoard();
		showPlayer();

		// Update previous states;		
		restorePreviousPlayerState();
		
		// Waiting for the user to determine where to put
		waitForInput();

		// Estimate the state of board
		estimateState();

		// 사용자에 의해 강제 종료 되었을 때
		if (exitByUser) {
			con_clearScr();
			showOutro();
			printf("\nDesigned by 황 태 경\n");

			StopRes(0);
			PlayRes(2, 1);
			getch();
			StopRes(2);
			break;
		}

		// 게임이 끝났을 때
		if (isOver()) {
			con_clearScr();
			showBoard();
			showPlayer();

			StopRes(0);
			PlayRes(1, 1);
			showVictroy();
			getch();
			StopRes(1);
			break;
		}

		switchPlayer();
	}
	return 0;
}