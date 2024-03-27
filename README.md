STRING CLASS
============
This is a implementation of simple String class in c++. 
All definitions is in ```myString.hpp```
____________
Class myString realize such methods:
``` size() - Returns the size (number of characters) of the string.
    length() - Same as size(), returns the length of the string.
    empty() - Returns true if the string is empty, false otherwise.
    clear() - Clears the contents of the string.
    append() - Appends a string or a portion of another string to the end of the current string.
    insert() - Inserts characters into the string at a specified position.
    erase() - Erases characters from the string at a specified position or within a specified range.
    replace() - Replaces a portion of the string with another string.
    substr() - Returns a substring of the string.
    find() - Finds the position of a substring within the string.
    find_first_of() - Finds the position of the first occurrence of any character in a specified set within the string.
    find_last_of() - Finds the position of the last occurrence of any character in a specified set within the string.
    compare() - Compares two strings.
    GetString() - Returns a pointer to a null-terminated character array with data equivalent to those stored in the string.
```
Most of methods are compatible with Windows CRT library

Heap checker classes
===================
This section consist of 2 classes:
* HeapChecker
* MemoryCheckpoint
  
All of above class is created using C runtime library

HeapChecker
===========
In this class we use concept of ```RAII``` which helps us to detect heap corruption.
We use ```_CrtCheckMemory()``` function to detect the heap corruption.<br>
```If we want to know where exactly is memory corrupted, we can use``` 
<pre>#define _CRT_DBG_MAP_ALLOC<br>
DEBUG_NEW expands to new(_NORMAL_BLOCK, __FILE__, __LINE__)</pre>
```to log the info about the place where memory is corrupted```

MemoryCheckpoint
================
In this class we can catch memory leaks and which line allocates the memory but not
dealocating it.
Use ```_CrtMemState``` to track the state of Heap before allocating and after
dealocating a memory. USe ```_CrtMemDifference``` function is used to check if 
memory leaks exist, and also using debug version of new we can track lines, where 
memory is leaked. 
```_CrtMemDumpAllObjectsSince``` - dump all object
```_CrtMemDumpStatistics``` - dump all memory blocks
