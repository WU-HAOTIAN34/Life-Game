#define SDL_MAIN_HANDLED
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <SDL.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "worldControl.h"
#include "model.h"


int main() {
	
	selfDefinedMap();
	return 0;




	/*FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	file = fopen("final.txt", "w");
	StoreMap(file);
	fclose(file);
	file = NULL;
	return 0;*/
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