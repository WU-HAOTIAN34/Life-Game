#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "game.h"


//use the global variable int** newMap and int** beforeMap
//delete newMap and create the updated newMap by beforeMap
//delete beforeMap and copy newMap after updating
void UpdateMap() {
	int i, j;
	//update the newMap
	FreeMap(newMap);
	CreateMap(newMap);
	// update every cell in the new world 
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			newMap[i][j] = JudgeIfAlive(beforeMap, i, j);
		}
	}
	//update the beforeMap
	FreeMap(beforeMap);
	CreateMap(beforeMap);
	//copy the newMap to beforeMap
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			beforeMap[i][j] = newMap[i][j];
		}
	}
}


//use the address of map int** destination, global variable int rowSize, int cilSize
//create a 2-D arry rowSize * colSize
void CreateMap(int** destination) {
	int i, j;
	//create a 2-D arry
	destination = (int**)malloc(sizeof(int*) * rowSize);
	for (i = 0; i < rowSize; i++) {
		destination[i] = (int*)malloc(sizeof(int) * colSize);
	}
	//initialize it with 0
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			destination[i][j] == 0;
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


//use the pointer of the file FILE* file to load the map
//successful return 1, otherwise return 0
int LoadMap(FILE* file) {
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


//use the pointer of the file FILE* file to store the last map
//successful return 1, otherwise return 0
int StoreMap(FILE* file) {
	fwrite(rowSize, sizeof(int), 1, file);
	fwrite(colSize, sizeof(int), 1, file);
	for (int i; i < rowSize; i++) {
		fwrite(newMap[i], sizeof(int), colSize, file);
	}
	return 1;
}
