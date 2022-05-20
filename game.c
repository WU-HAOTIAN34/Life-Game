#define SDL_MAIN_HANDLED
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <malloc.h>
#include "worldControl.h"
#include "game.h"


void Interface(FILE* file) {
	InitialSDL();
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
			printf("\033[47;31mSorry, the option you entered was invalid, please try again.\033[0m\n");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				
				break;
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				
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
	atexit(SDL_Quit); // set for clean-up on exit
	SDL_CreateWindowAndRenderer(800, 960, 0, &window, &renderer);
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
	offset1.x = 150;
	offset1.y = 865;
	offset1.h = 80;
	offset1.w = 200;
	SDL_RenderCopy(renderer, stopButtonTexture, NULL, &offset1);
	SDL_Rect offset2;
	offset2.x = 450;
	offset2.y = 865;
	offset2.h = 80;
	offset2.w = 200;
	SDL_RenderCopy(renderer, runButtonTexture, NULL, &offset2);
	SDL_RenderPresent(renderer);
	
}





void Apply(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect offset;
	offset.x = y * 800 / rowSize;
	offset.y = x * 800 / colSize + 60;
	offset.h = 800/rowSize;
	offset.w = 800/colSize;
	SDL_RenderCopy(renderer, texture, NULL, &offset);
}












