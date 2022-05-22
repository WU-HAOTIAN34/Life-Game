#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(worldControl)
{
  	RUN_TEST_CASE(worldControl, LoadMap_Return);
  	RUN_TEST_CASE(worldControl, LoadMap_LoadValue);
  	RUN_TEST_CASE(worldControl, StoreMap);
  	RUN_TEST_CASE(worldControl, CreateMap);  
	RUN_TEST_CASE(worldControl, FreeMap);  
	RUN_TEST_CASE(worldControl, AlterMap);  
	RUN_TEST_CASE(worldControl, JudgeIfAlive); 
	RUN_TEST_CASE(worldControl, UpdateMap_Return); 
	RUN_TEST_CASE(worldControl, UpdateMap_Value); 
	RUN_TEST_CASE(worldControl, StringToInt); 
}
