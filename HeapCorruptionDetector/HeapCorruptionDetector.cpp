#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <new>
#include <cassert>
#include <io.h>
#include <crtdbg.h>


#include "HeapChecker.hpp"
#include "myString.hpp"
#include "MemoryCheckpoint.hpp"

#ifdef _DEBUG
#define DEBUG_NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#else
#define DEBUG_NEW new
#endif 


int main()
{
    MEMORYCHECKPOINT;
    HeapChecker::Init(HeapChecker::OutputType::VSWINDOWS);
    HEAPCHECK;
    /*
    Here you can write your code 
    Using new class
    */
    return 0;
}
