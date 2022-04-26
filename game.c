#include <stdio.h>
#include <malloc.h>
#define SIZE 8

int** NodeChange(int** before, int** now) {
	int i, j;
	int** a = (int**)malloc(sizeof(int*) * 8);
	FreeMap(before);
	for (int i = 0; i < 8; i++) {
		a[i] = (int*)malloc(sizeof(int) * 8);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			a[i][j] = 1;
		}

	}
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			a[i][j] = JudgeIfLive(now, i, j);
		}
	}
	return a;
}


int JudgeIfLive(int** source, int x, int y) {
	int i, j;
	int num = 0;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (x + i >= 0 && x + i < SIZE && y + j >= 0 && y + j < SIZE && !(x == 0 && y == 0)) {
				if (source[x + i][y + j] == 0) {
					num++;
				}
			}
		}
	}
	if (source[x][y] == 1) {
		if (num == 2 || num == 3) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (source[x][y] == 0) {
		if (num == 3) {
			return 1;
		}
		else {
			return 0;
		}
	}
}


void PrintMap(int** source) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", source[i][j]);
		}
		printf("\n");
	}
}


void FreeMap(int** source) {
	for (int i = 0; i < 8; i++) {
		free(source[i]);
	}
	free(source);
}