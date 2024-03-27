#pragma once
#include <any>


class MemoryCheckpoint
{
public:
	MemoryCheckpoint(const char* pFile, const char* pFunction);
	~MemoryCheckpoint();

private:
	_CrtMemState m_Begin;
	const char* m_pFile;
	const char* m_pFunction;
};

#ifdef _DEBUG
#define MEMORYCHECKPOINT MemoryCheckpoint cp{__FILE__, __FUNCSIG__};
#else
#define MEMORYCHECKPOINT 
#endif // _DEBUG

