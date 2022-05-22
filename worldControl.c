#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "worldControl.h"


//use the global variable int** newMap and int** beforeMap
//update the newMap and compare with beforeMap
//if they are the same return 1, not return 0
int UpdateMap(void) {
	int i, j;
	int ifStop = 1;
	// update every cell in the new world 
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			newMap[i][j] = JudgeIfAlive(beforeMap, i, j);
		}
	}
	//compare with beforeMap
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


//use global variable int rowSize, int cilSize
//create a 2-D arry rowSize * colSize and return the address
int** CreateMap(void) {
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
			if (x + i >= 0 && x + i < rowSize && y + j >= 0 && y + j < colSize && i * i + j * j != 0) {
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
	else{
		return 0;
	}
}


//free the space of nowMap and beforeMap
void FreeMap(void) {
	//free every row
	for (int i = 0; i < rowSize; i++) {
		free(newMap[i]);
		free(beforeMap[i]);
	}
	free(newMap);
	free(beforeMap);
	newMap = NULL;
	beforeMap = NULL;

}


//use the pointer of the file FILE* file to load the map
//succeed return 1, false return 0
int LoadMap(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	int i = -1, j = 0, k=0;
	char ch1[1024];
	char row[1024];
	char col[1024];
	char delay1[1024];
	memset(ch1, '\0', 1024);
	memset(row, '\0', 1024);
	memset(col, '\0', 1024);
	memset(delay1, '\0', 1024);
	fgets(ch1, 1024, file);
	//divide the first lin into row, column and delay
	while (k < 3) {
		j = 0;
		i++;
		while ((int)ch1[i] >= 48 && (int)ch1[i] <= 57) {
			k++;
			while ((int)ch1[i] >= 48 && (int)ch1[i] <= 57) {
				if (k == 1) {
					delay1[j] = ch1[i];
				}
				if (k == 2) {
					row[j] = ch1[i];
				}
				if (k == 3) {
					col[j] = ch1[i];
				}
				j++;
				i++;
			}
			break;
		}
	}
	//convert the string to the integer
	delay = StringToInt(delay1);
	rowSize = StringToInt(row);
	colSize = StringToInt(col);
	//load the world in nowMap and beforeMap
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
	return 1;
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
	//store the row, col, delay
	char ch[1024];
	char* aim;
	memset(ch, '\0', 1024);
	aim = IntToString(delay);
	strcat(ch, aim);
	free(aim);
	strcat(ch, " ");
	aim = IntToString(rowSize);
	strcat(ch, aim);
	free(aim);
	strcat(ch, " ");
	aim = IntToString(colSize);
	strcat(ch, aim);
	free(aim);
	strcat(ch, "\n");
	fputs(ch, file);
	//store the final world
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
int StringToInt(char* str) {
	int i, j, k = 1;
	int len = strlen(str);
	
	int res = 0;
	// calculate each digit of number
	for (i = 0; i < len; i++) {
		for (j = 0; j < len - i - 1; j++) {
			k *= 10;
		}
		res += ((int)str[i] - 48) * k;
		k = 1;
	}
	return res;
}

//use the direction x,y change one cell in nowMap and beforeMap
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
