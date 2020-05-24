#pragma once

class CMemoryLick
{
public:
	char fileName[256];

	CMemoryLick();
	~CMemoryLick();
};

//----------------------------
// �޸� ����
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
// operator new ����ó��
//----------------------------
void operator delete (void* ptr, const char* file, int line);

//----------------------------
// ������ ����� delete
//----------------------------
void operator delete (void* ptr);

//----------------------------
// ���� ������ new
//----------------------------
#define new new(__FILE__, __LINE__)