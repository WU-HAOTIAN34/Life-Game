#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <SDL2/SDL.h>
#include "worldControl.h"
#include "model.h"
#include "game.h"


int main() {
	
	Interface();

	SDL_FreeSurface(aliveCellSurface);
	SDL_FreeSurface(deadCellSurface);
	SDL_FreeSurface(stopButtonSurface);
	SDL_FreeSurface(runButtonSurface);

	SDL_DestroyTexture(aliveCellTexture);
	SDL_DestroyTexture(deadCellTexture);
	SDL_DestroyTexture(stopButtonTexture);
	SDL_DestroyTexture(runButtonTexture);
	
	return 0;	
}