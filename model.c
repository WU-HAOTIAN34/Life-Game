#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "worldControl.h"
#include "model.h"
#include "game.h"




void SpecificStep() {





}


void AutomaticStep() {
	FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	file = NULL;
	InitialSDL();
	for (int i = 0; i < 8; i++) {
		PresentMap();
		UpdateMap();
	}






}






int LoadFinalMap(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	char ch1[1024];
	char row[1024];
	char col[1024];
	memset(ch1, '\0', 1024);
	memset(row, '\0', 1024);
	memset(col, '\0', 1024);
	newMap = CreateMap();
	for (int i = 0; i < rowSize; i++) {
		memset(ch1, '\0', 1024);
		fgets(ch1, 1024, file);
		for (int j = 0; j < colSize; j++) {
			newMap[i][j] = (int)(ch1[j]) - 48;
		}
	}

}