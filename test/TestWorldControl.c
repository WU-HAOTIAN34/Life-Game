#include "unity.h"
#include "unity_fixture.h"
#include <stdio.h>
#include "worldControl.h"

TEST_GROUP(worldControl);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
extern int** newMap;
extern int** beforeMap;
extern int delay;
extern int colSize;
extern int rowSize;

TEST_SETUP(worldControl)
{
  	//This is run before EACH TEST
  
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

