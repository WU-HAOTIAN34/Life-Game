#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "worldControl.h"
#include "model.h"
#include "game.h"
#include <SDL2/SDL.h>
//#include <SDL.h>



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
		SDL_Delay(delay);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 66 && event.button.x < 266 && event.button.y>670 && event.button.y < 850) {
					ifContinue = 0;
				}
				else if (event.button.x > 332 && event.button.x < 532 && event.button.y>670 && event.button.y < 850) {
					ifContinue = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				file = fopen("final.txt", "w");
				StoreMap(file);
				fclose(file);
				file = NULL;
				FreeMap();
				return;
			}
		}
		if (ifContinue == 1) {
			UpdateMap();
			iterationNum++;
		}
	}
	file = fopen("final.txt", "w");
	StoreMap(file);
	fclose(file);
	file = NULL;
	FreeMap();
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
		SDL_Delay(delay);	
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 66 && event.button.x < 266 && event.button.y>670 && event.button.y < 750) {
					ifContinue = 0;
				}
				else if (event.button.x > 332 && event.button.x < 532 && event.button.y>670 && event.button.y < 750) {
					ifContinue = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				file = fopen("final.txt", "w");
				StoreMap(file);
				fclose(file);
				file = NULL;
				FreeMap();
				return;
			}
		}
		if (ifContinue == 1) {
			end = UpdateMap();
			iterationNum++;
		}	
	}
	file = fopen("final.txt", "w");
	StoreMap(file);
	fclose(file);
	file = NULL;
	FreeMap();
}



void selfDefinedMap() {
	int ifready = 0;
	char entering[1024];
	ifContinue = 0;
	iterationNum = 0;
	memset(entering, '\0', 1024);
	printf("Please enter the number of rows: ");
	scanf("%[^\n]s", entering);
	getchar();
	if (IfNumValid(entering)) {
		printf("\n\033[47;31mInvalid entering. Expected entering: a number greater than 0.\033[0m\n");
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
		printf("\n\033[47;31mInvalid entering. Expected entering: a number greater than 0.\033[0m\n");
		return;
	}
	else {
		colSize = StringToInt(entering);
	}
	memset(entering, '\0', 1024);
	printf("Please enter the time of delay: ");
	scanf("%[^\n]s", entering);
	getchar();
	if (IfNumValid(entering)) {
		printf("\n\033[47;31mInvalid entering. Expected entering: a number greater than 0.\033[0m\n");
		return;
	}
	else {
		delay = StringToInt(entering);
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
				if (event.button.x >= leftSize && event.button.x <= leftSize + edgeSize * colSize 
					&& event.button.y >= topSize && event.button.y <= topSize + edgeSize * rowSize) {
					AlterMap((event.button.y - topSize) / edgeSize, (event.button.x - leftSize) / edgeSize);
				}
				else if (event.button.x > 332 && event.button.x < 532 && event.button.y>670 && event.button.y < 750) {
					ifContinue = 1;
					ifready = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				FILE* file = fopen("final.txt", "w");
				StoreMap(file);
				fclose(file);
				file = NULL;
				FreeMap();
				return;
			}
		}
		
	}
	iterationNum = 0;
	int end = 0;
	while (!end) {
		PresentMap();
		SDL_Delay(delay);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 66 && event.button.x < 266 && event.button.y>670 && event.button.y < 750) {
					ifContinue = 0;
				}
				else if (event.button.x > 332 && event.button.x < 532 && event.button.y>670 && event.button.y < 750) {
					ifContinue = 1;
				}
			}
			else if (event.type == SDL_QUIT) {
				FILE* file = fopen("final.txt", "w");
				StoreMap(file);
				fclose(file);
				file = NULL;
				FreeMap();
				return;
			}
		}
		if (ifContinue == 1) {
			end = UpdateMap();
			iterationNum++;
		}
	}
	FILE* file = fopen("final.txt", "w");
	StoreMap(file);
	fclose(file);
	file = NULL;
	FreeMap();
}




void ShowFinalMap() {
	FILE* file = fopen("final.txt", "r");
	LoadMap(file);
	fclose(file);
	file = NULL;
	InitialSDL();
	int i, j;
	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			if (newMap[i][j] == 1) {
				Apply(i, j, renderer, aliveCellTexture);
			}
			else if (newMap[i][j] == 0) {
				Apply(i, j, renderer, deadCellTexture);
			}
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	FreeMap();
}







/*
int LoadFinalMap(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	char ch1[1024];
	memset(ch1, '\0', 1024);
	newMap = CreateMap();
	while(fgets(ch1, 1024, file)!=EOF){
		printf("%d\n", strlen(ch1));
		for (int j = 0; j < strlen(ch1); j++) {
			newMap[i][j] = (int)(ch1[j]) - 48;
		}
	}




	for (int i = 0; i < rowSize; i++) {
		memset(ch1, '\0', 1024);
		fgets(ch1, 1024, file);
		for (int j = 0; j < colSize; j++) {
			newMap[i][j] = (int)(ch1[j]) - 48;
		}
	}

}

*/

int IfNumValid(char* num) {
	return (int)num[0] == 48 || num[0] == ' ' || num[strlen(num) - 1] == ' ' ||
		strspn(num, "0123456789") != strlen(num) ||  strlen(num) <= 0;
}
