#ifndef _INC_BOARD_CONTROL
#define _INC_BOARD_CONTROL

#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _INC_TIME
#include <time.h>
#endif

#ifndef _INC_CONSOLE_MANIPULATOR
#include "ConsoleManipulator.h"
#endif

// gloabl 변수 선언

/* X목판 크기 */
#define BOARD_SIZE 3
/* X목판 여백 */
#define BOARD_LEFT_MARGIN 20
#define BOARD_TOP_MARGIN 15
/* 처음 디폴트 플레이어 */
#define DEFAULT_PLAYER_NUMBER 1

/* 플레이어 위치 구조체 */
typedef struct { unsigned int x, y; } POS;

// 함수 선언

/* 보드판 초기화 */
void initBoard();

/* 보드판 제거 */
void removeBoard();

/* 인트로 출력 */
void showIntro();

/* 아웃트로 출력 */
void showOutro();

/* 이전 플레이어의 돌의 위치 복구 */
void restorePreviousPlayerState();

/* 보드의 좌표로 지정한 커서를 옮김 */
void gotoBoardCoord(const unsigned int x, const unsigned int y);

/* x, y 위치에 돌을 두기 */
int put(POS pos);

/* 돌을 두기 위한 조작 */
void waitForInput();

/* 보드의 설정값을 랜덤하게 설정함 */
void setRandomBoard();

/* 보드판의 형세를 파악함 */
void estimateState();

/* X목판 출력 */
void showBoard();

/* 현재 플레이어 출력 */
void showPlayer();

/* 다른 플레이어 번호 */
unsigned char anotherPlayer();

/* 승리 메시지를 출력하는 함수 */
void showVictroy();

/* 플레이어 교체 */
void switchPlayer();

/* 게임이 종료되면 승리한 플레이어의 번호를 리턴하는 함수 */
int isOver();

/* 키입력을 받아 KEY값을 넘겨주는 함수 */
KEY getInput();

#endif