#ifndef __WORLDCONTROL_H__
#define __WORLDCONTROL_H__


//use the global variable int**newMap and int** beforeMap
//delete newMap and create the updated newMap by beforeMap
//delete beforeMap and copy newMap after updating
void** UpdateMap();

//use map int**source and the coordinate of cell int x, int y
//if alive return 1, if dead return 0
int JudgeIfAlive(int** source, int x, int y);

//use the target int** source to delete it
void FreeMap(int** source);


int ReadMap(FILE* file);
int StoreMap(FILE* file);


#endif