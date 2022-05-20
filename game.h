#ifndef __GAME_H__
#define __GAME_H__
#include <SDL.h>

int iterationNum;
int ifContinue;
int rowSize;
int colSize;
int** newMap;
int** beforeMap;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* deadCellSurface;
SDL_Surface* aliveCellSurface;
SDL_Texture* deadCellTexture;
SDL_Texture* aliveCellTexture;
void InitialSDL();
void PresentMap();
void Apply(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture);



#endif