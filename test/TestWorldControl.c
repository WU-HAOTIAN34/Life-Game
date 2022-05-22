#include "unity.h"
#include "unity_fixture.h"
#include <stdio.h>
#include "worldControl.h"

TEST_GROUP(worldControl);

extern int** newMap;
extern int** beforeMap;
extern int delay;
extern int colSize;
extern int rowSize;

TEST_SETUP(worldControl)
{
  	
  
}

TEST_TEAR_DOWN(worldControl)
{

}

TEST(worldControl, LoadMap_Return)
{
	FILE* file = fopen("world.txt", "r");	
  	TEST_ASSERT_EQUAL(1, LoadMap(file));
	fclose(file);
	file = NULL;
	TEST_ASSERT_EQUAL(0, LoadMap(file));
  	
}
TEST(worldControl, LoadMap_LoadValue)
{
	FILE* file = fopen("world.txt", "r");	
  	TEST_ASSERT_EQUAL(1, LoadMap(file));
	TEST_ASSERT_EQUAL(1000, delay);
	TEST_ASSERT_EQUAL(10, rowSize);
	TEST_ASSERT_EQUAL(10, colSize);
	fclose(file);
	
}
TEST(worldControl, StoreMap)
{
  	FILE* file = fopen("world.txt", "r");	
  	TEST_ASSERT_EQUAL(1, StoreMap(file));
	fclose(file);
	file = NULL;
  	TEST_ASSERT_EQUAL(0, StoreMap(file));
}
TEST(worldControl, CreateMap)
{
	colSize = 10;
	rowSize = 10;
  	newMap = CreateMap();
  	TEST_ASSERT_EQUAL(0, newMap[1][2]);
  	TEST_ASSERT_EQUAL(0, newMap[1][7]);
  	TEST_ASSERT_EQUAL(0, newMap[2][3]);
  	TEST_ASSERT_EQUAL(0, newMap[6][9]);
  	TEST_ASSERT_EQUAL(0, newMap[5][7]);
  	TEST_ASSERT_EQUAL(0, newMap[7][1]);
  	TEST_ASSERT_EQUAL(0, newMap[9][9]);
}
TEST(worldControl, FreeMap)
{
  	colSize = 10;
	rowSize = 10;
  	newMap = CreateMap();
	beforeMap = CreateMap();
	FreeMap();
	TEST_ASSERT_EQUAL(NULL, newMap);
	TEST_ASSERT_EQUAL(NULL, beforeMap);
}
TEST(worldControl, AlterMap)
{
  	colSize = 10;
	rowSize = 10;
  	newMap = CreateMap();
	beforeMap = CreateMap();
	AlterMap(1, 1);
	TEST_ASSERT_EQUAL(1, newMap[1][1]);
	TEST_ASSERT_EQUAL(1, beforeMap[1][1]);
}
TEST(worldControl, JudgeIfAlive)
{
  	colSize = 10;
	rowSize = 10;
  	newMap = CreateMap();
	newMap[1][0] = 1;
	newMap[1][1] = 1;
	newMap[0][1] = 1;
	newMap[1][2] = 1;
	newMap[1][1] = 1;
	TEST_ASSERT_EQUAL(0, newMap[0][0]);
	TEST_ASSERT_EQUAL(1, newMap[1][1]);
	TEST_ASSERT_EQUAL(1, newMap[1][0]);
	TEST_ASSERT_EQUAL(0, newMap[3][1]);
}
TEST(worldControl, UpdateMap_Return)
{
  	colSize = 10;
	rowSize = 10;
  	newMap = CreateMap();
	beforeMap = CreateMap();
	TEST_ASSERT_EQUAL(1, UpdateMap());
	FreeMap();
	FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	TEST_ASSERT_EQUAL(0, UpdateMap());
}
TEST(worldControl, UpdateMap_Value)
{
  	colSize = 10;
	rowSize = 10;
  	FILE* file = fopen("world.txt", "r");
	LoadMap(file);
	fclose(file);
	UpdateMap();
	TEST_ASSERT_EQUAL(0, newMap[8][7]);
	TEST_ASSERT_EQUAL(1, newMap[0][0]);
	TEST_ASSERT_EQUAL(0, newMap[7][3]);
	TEST_ASSERT_EQUAL(1, newMap[8][1]);
	TEST_ASSERT_EQUAL(0, newMap[9][9]);
}
TEST(worldControl,StringToInt)
{
	char a[] = "123";
	char b[] = "0";
	char c[] = "72";
	TEST_ASSERT_EQUAL(123, StringToInt(a));
	TEST_ASSERT_EQUAL(0, StringToInt(b));
	TEST_ASSERT_EQUAL(72, StringToInt(c));
}
