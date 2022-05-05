#include <stdio.h>
#include <malloc.h>
#include "game.h"


//use the global variable int** newMap and int** beforeMap
//delete newMap and create the updated newMap by beforeMap
//delete beforeMap and copy newMap after updating
void UpdateMap() {
	int i, j;
	FreeMap(newMap);
	// create the new world a 2-D arry with rowSize * colSize
	newMap = (int**)malloc(sizeof(int*) * rowSize);
	for (i = 0; i < rowSize; i++) {
		newMap[i] = (int*)malloc(sizeof(int) * colSize);
	}
	// update every cell in the new world 
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			newMap[i][j] = JudgeIfAlive(beforeMap, i, j);
		}
	}
	//delete the beforeMap and create a new 2-D arry beforeMap
	FreeMap(beforeMap);
	beforeMap = (int**)malloc(sizeof(int*) * rowSize);
	for (i = 0; i < rowSize; i++) {
		beforeMap[i] = (int*)malloc(sizeof(int) * colSize);
	}
	//copy the newMap to beforeMap
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			beforeMap[i][j] = newMap[i][j];
		}
	}
}


//use map int**source and the coordinate of cell int x, int y
//if alive return 1, if dead return 0
int JudgeIfAlive(int** source, int x, int y) {
	int i, j;
	int num = 0;   //the alive cell around (x, y)
	//count the number of alive cells which are adjacent (x, y) 
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (x + i >= 0 && x + i < colSize && y + j >= 0 && y + j < rowSize && i * i + j * j != 0) {
				if (source[x + i][y + j] == 1) {
					num++;
				}
			}
		}
	}
	//judge if the cell will alive in next generation
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


//use the target int** source to delete it
void FreeMap(int** source) {
	//free every row
	for (int i = 0; i < rowSize; i++) {
		free(source[i]);
	}
	free(source);
}



int ReadMap(FILE* file) {
	int i;
	if (!fread(&rowSize, sizeof(int), 1, file) || !fread(&colSize, sizeof(int), 1, file)) {
		return 0;
	}
	newMap = (int**)malloc(sizeof(int*) * rowSize);
	for (i = 0; i < rowSize; i++) {
		newMap[i] = (int*)malloc(sizeof(int) * colSize);
	}
	for (i = 0; i < rowSize; i++) {
		if (!fread(newMap[i], sizeof(int), colSize, file)) {
			FreeMap(newMap);
			return 0;
		}
	}
	return 1;
}


int StoreMap(FILE* file) {
	fwrite(rowSize, sizeof(int), 1, file);
	fwrite(colSize, sizeof(int), 1, file);
	for (int i; i < rowSize; i++) {
		fwrite(newMap[i], sizeof(int), colSize, file);
	}
	return 1;
}



