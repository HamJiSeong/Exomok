#include "BoardControl.h"
#include "BGMLibrary.h"
#include "AI.h"
#include "console.h"
#include <string.h>


/* X목판 배열 */
unsigned int board[BOARD_SIZE][BOARD_SIZE];

/* 현재 플레이어 */
unsigned char player;

/* 돌의 모양 */
const char PLAYER1_STONE[3] = "●";
const char PLAYER2_STONE[3] = "○";

/* 위치 정보 */
POS PL_POS[2], p;

char exitByUser;

/* 게임 초기화 */
void initBoard() {
	srand(time(NULL));

	/* 위치 정보 초기화 */
	PL_POS[0].x = PL_POS[0].y = 1;
	PL_POS[1].x = PL_POS[1].y = BOARD_SIZE;

	/* 플레이 순서 초기화 */
	player = DEFAULT_PLAYER_NUMBER;

	/* 초기 플레이어 정보 저장 */
	p = PL_POS[player - 1];
	
	/* 랜덤으로 시작 BGM 로드 */
	if(rand()%2) LoadMp3(L"res/suri.mp3"); else LoadMp3(L"res/papapa.mp3");	
	LoadMp3(L"res/sejong.mp3");
	LoadMp3(L"res/gameover.mp3");

	/* BGM 재생 */
	PlayRes(0, 1);
}

void removeBoard() {}

void showIntro() {
	con_gotoXY(0,0);
	char *buf = (char*)malloc(sizeof(char)*256);
	FILE *fp = fopen("res/title.txt", "r");
	if (fp != NULL) {
		while(!feof(fp)) {
			if (fgets(buf, 256, fp) == NULL) {
				break;
			}
			printf("%s", buf);
		}
		fclose(fp);
	}
	free(buf);
	getch();
}

void showOutro() {
	con_gotoXY(0, 0);
	char *buf = (char*)malloc(sizeof(char) * 256);
	FILE *fp = fopen("res/title_NEXT.txt", "r");
	if (fp != NULL) {
		while (!feof(fp)) {
			if (fgets(buf, 256, fp) == NULL) {
				break;
			}
			printf("%s", buf);
		}
		fclose(fp);
	}
	free(buf);
}

void restorePreviousPlayerState() {
	p = PL_POS[player-1];
	gotoBoardCoord(p.x, p.y);
}

int isOver() {
	static const int x1[5] = { 0, 0, 0, 1, -1 };
	static const int y1[5] = { 0, 1, -1, 0, 0 };
	static const int x2[5] = { 0, 1, 1, -1, -1 };
	static const int y2[5] = { 0, 1, -1, 1, -1 };
	static unsigned int stage = BOARD_SIZE * BOARD_SIZE;
	
	if (--stage == 0) return player;

	int i, j, k, result;

	for (i = 1; i < BOARD_SIZE - 1; ++i) {
		for (j = 1; j < BOARD_SIZE - 1; ++j) {
			result = 1;
			for (k = 0; k < 5; ++k)
				result *= board[i + y1[k]][j + x1[k]] == player;
			if (result) return player;
			result = 1;
			for (k = 0; k < 5; ++k)
				result *= board[i + y2[k]][j + x2[k]] == player;
			if (result) return player;
		}
	}

	return 0;
}

int put(POS pos) {
	const unsigned int x = pos.x, y = pos.y;
	if (!board[y - 1][x - 1]) {
		board[y - 1][x - 1] = player;
		PL_POS[player - 1].x = x;
		PL_POS[player - 1].y = y;
		return 1;
	}
	return 0;
}

void waitForInput(){
	while(1){
		if (player == 1) {
			switch (getInput()) {
				// 착수 가능하면 착수 후 턴 종료
			case ENTER1: if (put(p)) return; else break;
			case ESC: exitByUser = 1; return;
				// Arrow
			case R:
				p.y = p.y > 1 ? p.y - 1 : p.y;
				break;
			case F:
				p.y = p.y < BOARD_SIZE ? p.y + 1 : p.y;
				break;
			case D:
				p.x = p.x > 1 ? p.x - 1 : p.x;
				break;
			case G:
				p.x = p.x < BOARD_SIZE ? p.x + 1 : p.x;
				break;
			default: break;
			}
		}
		else if (player == 2) {
			switch (getInput()) {
				// 착수
			case ENTER2: if (put(p)) return; else break;
			case ESC: exitByUser = 1; return;

				// Arrow
			case UP:
				p.y = p.y > 1 ? p.y - 1 : p.y;
				break;
			case DOWN:
				p.y = p.y < BOARD_SIZE ? p.y + 1 : p.y;
				break;
			case LEFT:
				p.x = p.x > 1 ? p.x - 1 : p.x;
				break;
			case RIGHT:
				p.x = p.x < BOARD_SIZE ? p.x + 1 : p.x;
				break;
			default: break;
			}
		}
		/*
		showBoard();
		showPlayer();
		*/
		gotoBoardCoord(p.x, p.y);
	}
}

void estimateState() {
	int **e = estimate(board);
	free(e);
}

void setRandomBoard() {
	int x, y, player = 1, stage = 0;
	while (stage<5) {
		x = rand() % BOARD_SIZE, y = rand() % BOARD_SIZE;
		if (!board[y][x]) {
			board[y][x] = player;
			player = player == 1 ? 2 : 1;
			++stage;
		}
	}
}

void showPlayer() {
	int x = 2 * BOARD_LEFT_MARGIN + 3 * BOARD_SIZE, y = BOARD_SIZE / 2 + BOARD_TOP_MARGIN;

	con_gotoXY(x, y - 1);
	con_outTxt("┌──────┐");
	con_gotoXY(x, y);
	con_outTxt("│Player %d → %s ", player, player - 1 ? PLAYER2_STONE : PLAYER1_STONE);
	con_gotoXY(x, y + 1);
	con_outTxt("└──────┘");
}



void showVictroy() {
	int x = 2 * (BOARD_SIZE / 3 + BOARD_LEFT_MARGIN - 1), y = 2;

	con_gotoXY(x, y - 1);
	con_outTxt("┌──────┐");

	con_gotoXY(x, y);
	con_outTxt("│Player %d win! │", player);

	con_gotoXY(x, y + 1);
	con_outTxt("└──────┘");
}

unsigned char anotherPlayer() {
	return !(player - 1) + 1;
}

void switchPlayer() {
	player = anotherPlayer();
}

void gotoBoardCoord(const unsigned int x, const unsigned int y) {
	con_gotoXY(2 * BOARD_LEFT_MARGIN + 2 * x, BOARD_TOP_MARGIN + y);	
}

void showBoard() {
	int i, j;
	
	for (i = 0; i < BOARD_SIZE; ++i) {
		for (j = 0; j < BOARD_SIZE; ++j) {
			gotoBoardCoord(j + 1 , i + 1);
			if (board[i][j] == 0)
				con_outTxt("┼");
			else if (board[i][j] == 1)
				con_outTxt("%s", PLAYER1_STONE);
			else if (board[i][j] == 2)
				con_outTxt("%s", PLAYER2_STONE);
		}		
	}

	for (i = 1; i <= BOARD_SIZE; ++i) {
		gotoBoardCoord(0, i);
		con_outTxt("├");
		gotoBoardCoord(BOARD_SIZE + 1, i);
		con_outTxt("┤");
	}

	// Top Pannel
	gotoBoardCoord(0, 0);
	con_outTxt("┌");
	for (i = 1; i <= BOARD_SIZE; ++i) con_outTxt("┬");
	con_outTxt("┐");

	
	// Bottom Pannel
	gotoBoardCoord(0, BOARD_SIZE + 1);
	con_outTxt("└");
	for (i = 1; i <= BOARD_SIZE; ++i) con_outTxt("┴");
	con_outTxt("┘");
}

KEY getInput() {
	int c = getch();
	switch (c)
	{
		case 13:	return ENTER;
		case 27:	return ESC;
		// Player 1 Input
		case 122:	return ENTER1;
		case 100: case 68: return D;
		case 103: case 71: return G;
		case 114: case 82: return R;
		case 102: case 70: return F;
		// Player 2 Input
		case 47:	return ENTER2;
		default:break;
	}

	if (c == 224) {
		c = getch();
		switch (c) {
		case 72: return UP;
		case 80: return DOWN;
		case 75: return LEFT;
		case 77: return RIGHT;
		default: break;
		}
	}
	return ETC;
}