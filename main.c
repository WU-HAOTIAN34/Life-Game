#define SDL_MAIN_HANDLED

#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>
//#include "controlFunctions.h"

#include <malloc.h>

void ApplySurface(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect offset;
	offset.x = y*50;
	offset.y = x*50;
	offset.h = 30;
	offset.w = 30;
	SDL_RenderCopy(renderer, texture, NULL, &offset);
	

}




int main(int argc, char* args[]) {
	int i, j;

	int num1[5][8] = { {1,1,1,0,1,0,1,0},
						{1,0,0,0,1,0,1,0},
						{1,1,1,1,1,0,0,0},
						{1,0,1,0,1,0,1,1},
						{1,0,1,0,1,0,1,1}, };

	int num2[5][8] = { {0,0,0,0,0,0,0,1},
						{1,0,0,0,1,0,1,0},
						{1,1,1,1,1,0,0,0},
						{1,0,1,1,1,1,0,0},
						{1,0,0,0,1,0,1,0}, };

	SDL_Renderer* renderer = NULL;

	SDL_Surface* white_surface = NULL;
	SDL_Surface* square_surface = NULL;
	SDL_Surface* circle_surface = NULL;

	SDL_Texture* white_texture = NULL;
	SDL_Texture* square_texture = NULL;
	SDL_Texture* circle_texture = NULL;


	SDL_Window* window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

	atexit(SDL_Quit); // set for clean-up on exit

	SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Circles eat squares");
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	circle_surface = SDL_LoadBMP("images/circle.bmp");
	white_surface = SDL_LoadBMP("images/white.bmp");
	square_surface = SDL_LoadBMP("images/square.bmp");



	circle_texture = SDL_CreateTextureFromSurface(renderer, circle_surface);
	white_texture = SDL_CreateTextureFromSurface(renderer, white_surface);
	square_texture = SDL_CreateTextureFromSurface(renderer, square_surface);

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num1[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if(num1[i][j]==0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(1000);


	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num2[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num2[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);



	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num1[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num1[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(1000);


	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num2[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num2[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);





	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num1[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num1[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(1000);


	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num2[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num2[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);





	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num1[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num1[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(1000);


	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (num2[i][j] == 1) {
				ApplySurface(i, j, renderer, circle_texture);
			}
			else if (num2[i][j] == 0) {
				ApplySurface(i, j, renderer, square_texture);
			}
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);




	return 0;
}







//int main(void)
//{
//	int delay = 160;
//
//	init();   // setup the game data
//	render(); // render initial state
//
//	while (true) {      // game loop
//
//		input();            // keyboard input
//
//		if (!update())     // update and ...
//			gameover();         // check if finished
//
//		render();           // render new state
//
//		SDL_Delay(delay); // time between frames (ms)
//	}
//	return 0;
//}