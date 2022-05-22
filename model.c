#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "worldControl.h"
#include "model.h"
#include "game.h"



//this model allow users to enter a step, 
//then the world will iteration to this step
void SpecificStep() {
	  // initialize the global variables
	ifContinue = 0;
	iterationNum = 0;
	char aim[1024];
	  //load world and recive entering
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
	// draw thw window and deal with events
	InitialSDL();
	SDL_Event event;
	while (iterationNum <= aimIterationNum) {
		PresentMap();
		SDL_Delay(delay);
		while (SDL_PollEvent(&event)) {
			    // clicking event: if click stop button, stop, if click run button, run 
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > 66 && event.button.x < 266 && event.button.y>670 && event.button.y < 850) {
					ifContinue = 0;
				}
				else if (event.button.x > 332 && event.button.x < 532 && event.button.y>670 && event.button.y < 850) {
					ifContinue = 1;
				}
			}
						// if click quit, free array and store
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
	// end free and store
	file = fopen("final.txt", "w");
	StoreMap(file);
	fclose(file);
	file = NULL;
	FreeMap();
}


//in this model the world will continue to iterate until the end
void AutomaticStep() {
	int end = 0; // judge if the world is final
	ifContinue = 0;
	iterationNum = 0;
	// load world and initialize SDL
	FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	file = NULL;
	InitialSDL();
	// draw thw window and deal with events
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


//this model allow users to customize the world
//users need to enter the number of rows, columns, and time of delay
//users can initialize the world by clicking to define the state of cell
void selfDefinedMap() {
	int ifready = 0; // judge if users have finished initializing
	char entering[1024];
	ifContinue = 0;
	iterationNum = 0;
	//recive row, column and delay
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
	//initialize SDL and the world
	InitialSDL();
	newMap = CreateMap();
	beforeMap = CreateMap();
	SDL_Event event;
	while (!ifready) {
		PresentMap();
		SDL_Delay(250);
		while (SDL_PollEvent(&event)) {
			//click event: click in the range of a cell, it will change the state, alive to dead, dead to alive
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x >= leftSize && event.button.x <= leftSize + edgeSize * colSize 
					&& event.button.y >= topSize && event.button.y <= topSize + edgeSize * rowSize) {
					AlterMap((event.button.y - topSize) / edgeSize, (event.button.x - leftSize) / edgeSize);
				}
				//click run button, finish innitializing 
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
	//continue iterating until the end
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


//show the final world stored in final.txt
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


//judge if the entering number string is valid:
//doesn't begin with space and 0, doesn't end with space 
//and no characters other than numbers 
int IfNumValid(char* num) {
	return (int)num[0] == 48 || num[0] == ' ' || num[strlen(num) - 1] == ' ' ||
		strspn(num, "0123456789") != strlen(num) ||  strlen(num) <= 0;
}
