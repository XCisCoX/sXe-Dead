#pragma once
#include "Includes.h"
#define UNKNOWVER 0
#define IS3266OPENGL 1
#define IS3266SOFTWARE 2
#define IS4554OPENGL 3
#define IS4554SOFTWARE 4
static  int CSVER=0;
int CheckVersion(HANDLE hProcess);
