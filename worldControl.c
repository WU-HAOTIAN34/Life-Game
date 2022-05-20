#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "worldControl.h"


//use the global variable int** newMap and int** beforeMap
//delete newMap and create the updated newMap by beforeMap
//delete beforeMap and copy newMap after updating
int UpdateMap() {
	int i, j;
	int ifStop = 1;
	// update every cell in the new world 
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			newMap[i][j] = JudgeIfAlive(beforeMap, i, j);
		}
	}
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			if (beforeMap[i][j] != newMap[i][j]) {
				ifStop = 0;
				break;
			}
		}
		if (ifStop == 0) {
			break;
		}
	}
	//copy the newMap to beforeMap
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			beforeMap[i][j] = newMap[i][j];
		}
	}
	return ifStop;
}


//use the address of map int** destination, global variable int rowSize, int cilSize
//create a 2-D arry rowSize * colSize
int** CreateMap() {
	int i, j;
	int** destination;
	//create a 2-D arry
	destination = (int**)malloc(sizeof(int*) * rowSize);
	for (i = 0; i < rowSize; i++) {
		destination[i] = (int*)malloc(sizeof(int) * colSize);
	}
	//initialize it with 0
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			destination[i][j] = 0;
		}
	}
	return destination;
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
//succeed return 1, false return 0, the content of file is wrong return -1
int LoadMap(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	char ch1[1024];
	char row[1024];
	char col[1024];
	memset(ch1, '\0', 1024);
	memset(row, '\0', 1024);
	memset(col, '\0', 1024);
	int i = 0;
	fgets(ch1, 1024, file);
	while (ch1[i] != ' ') {
		row[i] = ch1[i];
		i++;
	}
	i++;
	int j = 0;
	while (ch1[i] != '\n') {
		col[j] = ch1[i];
		j++;
		i++;
	}
	colSize = StringToInt(col);
	rowSize = StringToInt(row);
	newMap = CreateMap();
	for (int i = 0; i < rowSize; i++) {
		memset(ch1, '\0', 1024);
		fgets(ch1, 1024, file);
		for (int j = 0; j < colSize; j++) {
			newMap[i][j] = (int)(ch1[j]) - 48;
		}
	}
	beforeMap = CreateMap();
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			beforeMap[i][j] = newMap[i][j];
		}
	}

	/*char ch;
	CreateMap(newMap);
	fgetc(file);
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			ch = fgetc(file);
			if (ch == EOF || ch == '\n' || !((int)ch == 49 || (int)ch == 48)) {
				FreeMap(newMap);
				return -1;
			}
			else {
				newMap[i][j] = (int)ch - 48;
			}
		}
		ch = fgetc(file);
		if (ch == EOF && ch != '\n') {
			FreeMap(newMap);
			return -1;
		}
	}*/
}


//use the int x, covert it to a string, return the pointer of the string
char* IntToString(int x) {
	int num = x;
	int digit = 1;
	char* res;
	while (num /= 10) {
		digit += 1;
	}
	res = (char*)malloc(sizeof(char) * (digit + 1));
	memset(res, '\0', digit + 1);
	for (int i = 0; i < digit; i++) {
		res[digit - 1 - i] = (char)(x % 10 + 48);
		x /= 10;
	}
	return res;
}


//use the pointer of the file FILE* file to store the last map
//successful return 1, otherwise return 0
int StoreMap(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			fputc(newMap[i][j] + 48, file);
		}
		if (i != rowSize - 1) {
			putc('\n', file);
		}
	}
	return 1;
}


//use the pointer of a string char* string, convert it to the integer and return
int StringToInt(char* string) {
	int len = strlen(string);
	int pow = 1;
	int res = 0;
	for (int i = 0; i < len; i++) {
		res += ((int)string[len - i - 1] - 48) * pow;
		pow *= 10;
	}
	return res;
}


void AlterMap(int x, int y) {
	if (newMap[x][y] == 0) {
		newMap[x][y] = 1;
		beforeMap[x][y] = 1;
	}
	else {
		newMap[x][y] = 0;
		beforeMap[x][y] = 0;
	}
}
