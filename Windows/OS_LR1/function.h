#ifndef FUNCTION_H
#define FUNCTION_H
#include <windows.h>
#include "flow.h"
#include "nodes.h"
#include <iostream>

using namespace std;

//CRITICAL_SECTION section;

DWORD WINAPI ThreadFunc(PVOID);
BOOL WINAPI HandlerRoutine(DWORD);

#endif // FUNCTION_H
