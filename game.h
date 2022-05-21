#ifndef __GAME_H__
#define __GAME_H__
//#include <SDL.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>


char message[100];
int iterationNum;
int aimIterationNum;
int ifContinue;
int topSize;
int leftSize;
int edgeSize;
int rowSize;
int colSize;
int delay;
int** newMap;
int** beforeMap;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* deadCellSurface;
SDL_Surface* aliveCellSurface;
SDL_Surface* stopButtonSurface;
SDL_Surface* runButtonSurface;
SDL_Surface* messageSurface;
SDL_Texture* deadCellTexture;
SDL_Texture* aliveCellTexture;
SDL_Texture* stopButtonTexture;
SDL_Texture* runButtonTexture;
SDL_Texture* messageTexture;
SDL_Color textColor;
TTF_Font *font;
void InitialSDL();
void PresentMap();
void Apply(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture);
void Interface();


#endif
