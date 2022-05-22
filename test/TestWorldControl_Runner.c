#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(worldControl)
{
  	RUN_TEST_CASE(worldControl, LoadMap_Return);
  	RUN_TEST_CASE(worldControl, LoadMap_LoadValue);
  	RUN_TEST_CASE(worldControl, StoreMap);
  	RUN_TEST_CASE(worldControl, CreateMap);  
}
