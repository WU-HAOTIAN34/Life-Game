#ifndef __GAME_H__
#define __GAME_H__
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>


char message[100]; //world information printed in the window
int iterationNum;	//the number of iteration
int aimIterationNum; // the defined number of iteration
int ifContinue;	  //judge if the iteration should stop or continue
int topSize;	//the distance between the world and the top of the window
int leftSize;	//the distance between the world and the left of the window
int edgeSize;	//the size of the edge of a cell
int rowSize;	// the number of rows
int colSize;	//the number of columns
int delay;		//the time of delay
int** newMap;	//the 2-D array for new generation
int** beforeMap;  //the 2-D array for old generation
SDL_Window* window;	
SDL_Renderer* renderer;
//surface of the images and text
SDL_Surface* deadCellSurface;
SDL_Surface* aliveCellSurface;
SDL_Surface* stopButtonSurface;
SDL_Surface* runButtonSurface;
SDL_Surface* messageSurface;
//texture of the images and text
SDL_Texture* deadCellTexture;
SDL_Texture* aliveCellTexture;
SDL_Texture* stopButtonTexture;
SDL_Texture* runButtonTexture;
SDL_Texture* messageTexture;
//SDL_ttf
SDL_Color textColor;
TTF_Font *font;

//print the interface of the program
void Interface();

//initialize the SDL
void InitialSDL();

//draw the window, management the information string, world and button
void PresentMap();

//draw a cell in the window
void Apply(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture);


#endif
