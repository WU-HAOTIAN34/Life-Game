#ifndef __WORLDCONTROL_H__
#define __WORLDCONTROL_H__


//use the global variable int**newMap and int** beforeMap
//delete newMap and create the updated newMap by beforeMap
//delete beforeMap and copy newMap after updating
void** UpdateMap();

//use the address of map int** destination, global variable int rowSize, int cilSize
//create a 2-D arry rowSize * colSize
void CreateMap(int** destination);

//use map int**source and the coordinate of cell int x, int y
//if alive return 1, if dead return 0
int JudgeIfAlive(int** source, int x, int y);

//use the target int** source to delete it
void FreeMap(int** source);

//use the pointer of the file FILE* file to load the map
//successful return 1, otherwise return 0
int LoadMap(FILE* file);

//use the pointer of the file FILE* file to store the last map
//successful return 1, otherwise return 0
int StoreMap(FILE* file);


#endif