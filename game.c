#include <stdio.h>
#include <malloc.h>
#define SIZE 8

int** NodeChange(int* next, int* now) {
	int i, j;
	int (*before) = (int(*))malloc(sizeof(int) * SIZE * SIZE);
	free(now);
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {

		}
	}
}


int JudgeIflife(int** a, int x, int y) {
	int i, j;
	int num = 0;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (x + i >= 0 && x + i < SIZE && y + j >= 0 && y + j < SIZE && !(x == 0 && y == 0)) {
				if (a[x + i][y + j] == 0) {
					num++;
				}
			}
		}
	}
	if (a[x][y] == 1) {
		if (num == 2 || num == 3) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (a[x][y] == 0) {
		if (num == 3) {
			return 1;
		}
		else {
			return 0;
		}
	}
}