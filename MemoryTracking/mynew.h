#pragma once

class CMemoryLick
{
public:
	char fileName[256];

	CMemoryLick();
	~CMemoryLick();
};

//----------------------------
// 메모리 정보
//----------------------------
struct MemoryInfo
{
	char fileName[256];
	void* ptr;
	int size;
	int Line;
};

//----------------------------
// operator new
//----------------------------
void* operator new (size_t size, const char* file, int line);

//----------------------------
// operator new 예외처리
//----------------------------
void operator delete (void* ptr, const char* file, int line);

//----------------------------
// 실제로 사용할 delete
//----------------------------
void operator delete (void* ptr);

//----------------------------
// 내가 정의한 new
//----------------------------
#define new new(__FILE__, __LINE__)