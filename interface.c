#include <stdio.h>
#include "game.h"
#include <malloc.h>


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