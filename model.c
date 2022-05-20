#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "worldControl.h"
#include "model.h"
#include "game.h"




void SpecificStep() {
	ifContinue = 0;
	iterationNum = 0;
	char aim[1024];
	FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	file = NULL;
	printf("Please enter the wanted number of iterations: ");
	scanf("%[^\n]s", aim);
	if (IfNumValid(aim)) {
		printf("\n\033[47;31mInvalid entering. Expected entering: a number greater than 1.\033[0m\n");
		return;
	}
	else {
		aimIterationNum = StringToInt(aim);
	}
	InitialSDL();
	SDL_Event event;
	while (iterationNum <= aimIterationNum) {
		PresentMap();
		SDL_Delay(1000);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 150 && event.button.x < 350 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 0;
				}
				else if (event.button.x > 450 && event.button.x < 650 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (ifContinue == 1) {
			UpdateMap();
			iterationNum++;
		}
	}
}


void AutomaticStep() {
	int end = 0;
	ifContinue = 0;
	iterationNum = 0;
	FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	file = NULL;
	InitialSDL();
	SDL_Event event;
	while (!end) {
		PresentMap();
		SDL_Delay(1000);	
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 150 && event.button.x < 350 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 0;
				}
				else if (event.button.x > 450 && event.button.x < 650 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (ifContinue == 1) {
			end = UpdateMap();
			iterationNum++;
		}	
	}
}



void selfDefinedMap() {
	int ifready = 0;
	char entering[1024];
	memset(entering, '\0', 1024);
	printf("Please enter the number of rows: ");
	scanf("%[^\n]s", entering);
	getchar();
	if (IfNumValid(entering)) {
		printf("\n\033[47;31mInvalid entering. Expected entering: a number greater than 1.\033[0m\n");
		return;
	}
	else {
		rowSize = StringToInt(entering);
	}
	memset(entering, '\0', 1024);
	printf("Please enter the number of columns: ");
	scanf("%[^\n]s", entering);
	getchar();
	if (IfNumValid(entering)) {
		printf("\n\033[47;31mInvalid entering. Expected entering: a number greater than 1.\033[0m\n");
		return;
	}
	else {
		colSize = StringToInt(entering);
	}
	InitialSDL();
	newMap = CreateMap();
	beforeMap = CreateMap();
	SDL_Event event;
	while (!ifready) {
		PresentMap();
		SDL_Delay(250);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x >= 0 && event.button.x <= 800 && event.button.y >= 60 && event.button.y <= 860) {
					AlterMap((event.button.y - 60) / (800 / rowSize), event.button.x / (800 / colSize));
				}
				else if (event.button.x > 450 && event.button.x < 650 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 1;
					ifready = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		
	}
	iterationNum = 0;
	int end = 0;
	while (!end) {
		PresentMap();
		SDL_Delay(1000);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 150 && event.button.x < 350 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 0;
				}
				else if (event.button.x > 450 && event.button.x < 650 && event.button.y>865 && event.button.y < 945) {
					ifContinue = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (ifContinue == 1) {
			end = UpdateMap();
			iterationNum++;
		}
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



int IfNumValid(char* num) {
	return (int)num[0] == 48 || num[0] == ' ' || num[strlen(num) - 1] == ' ' ||
		strspn(num, "0123456789") != strlen(num) ||  strlen(num) <= 0;
}
