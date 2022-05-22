#ifndef __MODEL_H__
#define __MODEL_H__

//this model allow users to enter a step, 
//then the world will iteration to this step
void SpecificStep();

//in this model the world will continue to iterate until the end
void AutomaticStep();

//this model allow users to customize the world
//users need to enter the number of rows, columns, and time of delay
//users can initialize the world by clicking to define the state of cell
void selfDefinedMap();

//show the final world stored in final.txt
void ShowFinalMap();

//judge if the entering number string is valid:
//doesn't begin with space and 0, doesn't end with space 
//and no characters other than numbers 
int IfNumValid(char* num);

#endif