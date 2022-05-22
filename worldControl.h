#ifndef __WORLDCONTROL_H__
#define __WORLDCONTROL_H__


//use the global variable int** newMap and int** beforeMap
//update the newMap and compare with beforeMap
//if they are the same return 1, not return 0
int UpdateMap();

//use global variable int rowSize, int cilSize
//create a 2-D arry rowSize * colSize and return the address
int** CreateMap();

//use map int**source and the coordinate of cell int x, int y
//if alive return 1, if dead return 0
int JudgeIfAlive(int** source, int x, int y);

//free the space of nowMap and beforeMap
void FreeMap();

//use the pointer of the file FILE* file to load the map
//succeed return 1, false return 0, the content of file is wrong return -1
int LoadMap(FILE* file);

//use the int x, covert it to a string, return the pointer of the string
char* IntToString(int x);

//use the pointer of the file FILE* file to store the last map
//successful return 1, otherwise return 0
int StoreMap(FILE* file);

//use the pointer of a string char* string, convert it to the integer and return
int StringToInt(char* str);

//use the direction x,y change one cell in nowMap and beforeMap
void AlterMap(int x, int y);

#endif
