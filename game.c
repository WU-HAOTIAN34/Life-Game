#define SDL_MAIN_HANDLED
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "SDL.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "model.h"
#include "worldControl.h"
#include "game.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

void Interface() {
	
	char enter[100];	//recive entering 
	int option = 0;		// obtain the correct character
	memset(enter, '\0', 100);
	// option
	
	while (option != 5) {
		printf("\nPlease choose an option: \n\n1. Register an account\n2. Login\n");
		printf("3. Search for books\n4. Display all books\n5. Quit\nOption: ");
		scanf("%[^\n]s", enter);
		getchar();
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 54) {
			printf("\n\033[47;31mSorry, the option you entered was invalid, please try again.\033[0m\n");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				
				SpecificStep();
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				getchar();
				break;
			case 2:
				
				AutomaticStep();
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				
				break;
			case 3:
				
				selfDefinedMap();
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				
				break;
			case 4:
				
				ShowFinalMap();
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				
				break;
			case 5:
			default:
				break;
			}
		}
	}
}



void InitialSDL() {
	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
	}
	if (TTF_Init() < 0) {
		printf("TTF init failed: %s\n", TTF_GetError());
	}
	else {
		font = TTF_OpenFont("font/FreeSansBold.ttf", 40);
		if(font == NULL) {
			printf("Erroe loading font. %s\n", TTF_GetError());
		}
	}
	textColor.r = 0;
  	textColor.g = 0;
  	textColor.b = 0;
	atexit(SDL_Quit); // set for clean-up on exit
	SDL_CreateWindowAndRenderer(600, 760, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Circles eat squares");
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	deadCellSurface = SDL_LoadBMP("images/dead.bmp");
	aliveCellSurface = SDL_LoadBMP("images/alive.bmp");
	stopButtonSurface = SDL_LoadBMP("images/stop.bmp");
	runButtonSurface = SDL_LoadBMP("images/run.bmp");
	
	deadCellTexture = SDL_CreateTextureFromSurface(renderer, deadCellSurface);
	aliveCellTexture = SDL_CreateTextureFromSurface(renderer, aliveCellSurface);
	stopButtonTexture = SDL_CreateTextureFromSurface(renderer, stopButtonSurface);
	runButtonTexture = SDL_CreateTextureFromSurface(renderer, runButtonSurface);
}




void PresentMap() {
	int i, j;
	if (rowSize <= colSize) {
		edgeSize = 600 / colSize;
	}
	else {
		edgeSize = 600 / rowSize;
	}
	topSize = 60 + (600 - edgeSize * rowSize) / 2;
	leftSize = (600 - edgeSize * colSize) / 2;
	
	SDL_RenderClear(renderer);
	sprintf(message, "Generation: %d  Delay: %d  Status: %s", iterationNum, delay, ifContinue ? "Running" : "Pause");
	messageSurface = TTF_RenderText_Solid(font, message, textColor);
  	messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);	
	

	SDL_Rect offset0;
	offset0.x = 5;
	offset0.y = 10;
	offset0.h = 40;
	offset0.w = 590;
	SDL_RenderCopy(renderer, messageTexture, NULL, &offset0);



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
	SDL_Rect offset1;
	offset1.x = 66;
	offset1.y = 670;
	offset1.h = 80;
	offset1.w = 200;
	SDL_RenderCopy(renderer, stopButtonTexture, NULL, &offset1);
	SDL_Rect offset2;
	offset2.x = 332;
	offset2.y = 670;
	offset2.h = 80;
	offset2.w = 200;
	SDL_RenderCopy(renderer, runButtonTexture, NULL, &offset2);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(messageSurface);
  	SDL_DestroyTexture(messageTexture);
	
}




void Apply(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect offset;
	
	offset.x = y * edgeSize + leftSize;
	offset.y = x * edgeSize + topSize;
	offset.h = edgeSize;
	offset.w = edgeSize;

	SDL_RenderCopy(renderer, texture, NULL, &offset);
}
