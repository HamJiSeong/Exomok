#include "AI.h"

int ** estimate(const unsigned int(*arr)[BOARD_SIZE])
{
	int (*estimation)[BOARD_SIZE] = (int *)malloc(sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			estimation[i][j] = 0;
	static const int x[4] = {0,0,1,-1};
	static const int y[4] = {1,-1,0,0};
	int v;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (arr[i][j] == 1) {
				v = 0;
				for (int k = 0; k < 4; ++k){
					if (i + y[k] >= 0 && i + y[k] < BOARD_SIZE && j + x[k] >= 0 && j + x[k] < BOARD_SIZE) {
						if (arr[i][j] == 1) ++v;
						else if(arr[i][j] == 2) {
							v = 0;
							break;
						}
					}
				}
				for (int k = 0; k < 4; ++k) {
					if (i + y[k] >= 0 && i + y[k] < BOARD_SIZE && j + x[k] >= 0 && j + x[k] < BOARD_SIZE) {
						estimation[i+y[k]][j+x[k]] += v;
					}
				}
			}
			else if (arr[i][j] == 2) {
				v = 0;
				for (int k = 0; k < 4; ++k) {
					if (i + y[k] >= 0 && i + y[k] < BOARD_SIZE && j + x[k] >= 0 && j + x[k] < BOARD_SIZE) {
						if (arr[i][j] == 2) ++v;
						else if (arr[i][j] == 1) {
							v = 0;
							break;
						}
					}
				}
				for (int k = 0; k < 4; ++k) {
					if (i + y[k] >= 0 && i + y[k] < BOARD_SIZE && j + x[k] >= 0 && j + x[k] < BOARD_SIZE) {
						estimation[i + y[k]][j + x[k]] -= v;
					}
				}
			}
		}
	}
	return estimation;
}
