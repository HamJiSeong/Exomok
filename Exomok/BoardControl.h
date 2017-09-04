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

// gloabl ���� ����

/* X���� ũ�� */
#define BOARD_SIZE 3
/* X���� ���� */
#define BOARD_LEFT_MARGIN 20
#define BOARD_TOP_MARGIN 15
/* ó�� ����Ʈ �÷��̾� */
#define DEFAULT_PLAYER_NUMBER 1

/* �÷��̾� ��ġ ����ü */
typedef struct { unsigned int x, y; } POS;

// �Լ� ����

/* ������ �ʱ�ȭ */
void initBoard();

/* ������ ���� */
void removeBoard();

/* ��Ʈ�� ��� */
void showIntro();

/* �ƿ�Ʈ�� ��� */
void showOutro();

/* ���� �÷��̾��� ���� ��ġ ���� */
void restorePreviousPlayerState();

/* ������ ��ǥ�� ������ Ŀ���� �ű� */
void gotoBoardCoord(const unsigned int x, const unsigned int y);

/* x, y ��ġ�� ���� �α� */
int put(POS pos);

/* ���� �α� ���� ���� */
void waitForInput();

/* ������ �������� �����ϰ� ������ */
void setRandomBoard();

/* �������� ������ �ľ��� */
void estimateState();

/* X���� ��� */
void showBoard();

/* ���� �÷��̾� ��� */
void showPlayer();

/* �ٸ� �÷��̾� ��ȣ */
unsigned char anotherPlayer();

/* �¸� �޽����� ����ϴ� �Լ� */
void showVictroy();

/* �÷��̾� ��ü */
void switchPlayer();

/* ������ ����Ǹ� �¸��� �÷��̾��� ��ȣ�� �����ϴ� �Լ� */
int isOver();

/* Ű�Է��� �޾� KEY���� �Ѱ��ִ� �Լ� */
KEY getInput();

#endif