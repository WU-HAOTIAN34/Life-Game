#ifndef __WORLDCONTROL_H__
#define __WORLDCONTROL_H__


//use the global variable int**newMap and int** beforeMap
//delete newMap and create the updated newMap by beforeMap
//delete beforeMap and copy newMap after updating
int UpdateMap();

//use the address of map int** destination, global variable int rowSize, int cilSize
//create a 2-D arry rowSize * colSize
int** CreateMap();

//use map int**source and the coordinate of cell int x, int y
//if alive return 1, if dead return 0
int JudgeIfAlive(int** source, int x, int y);

//use the target int** source to delete it
void FreeMap(int** source);

//use the pointer of the file FILE* file to load the map
//succeed return 1, false return 0, the content of file is wrong return -1
int LoadMap(FILE* file);

//use the int x, covert it to a string, return the pointer of the string
char* IntToString(int x);

//use the pointer of the file FILE* file to store the last map
//successful return 1, otherwise return 0
int StoreMap(FILE* file);

//use the pointer of a string char* string, convert it to the integer and return
int StringToInt(char* string);

void AlterMap(int x, int y);

#endif