#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "mynew.h"

//----------------------------
// 기존 new #undef
//----------------------------
#undef new

#define INFO_COUNT 100

CMemoryLick memoryLick;
MemoryInfo* memoryInfo[INFO_COUNT] = { nullptr };

//------------------------------
// Alloc_YYYYMMDD_HHMMSS.txt
//------------------------------
CMemoryLick::CMemoryLick()
{
	tm timeInfo;
	time_t nowTime = time(NULL);
	localtime_s(&timeInfo, &nowTime);

	sprintf(this->fileName, "Alloc_%d-%d-%d_%d.%d.%d.txt", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1,
		timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

//----------------------------
// operator new
//----------------------------
void* operator new(size_t size, const char* file, int line)
{
	void* ptr = malloc(size);

	for (int i = 0; i < INFO_COUNT; i++)
	{
		if (memoryInfo[i] != nullptr)
		{
			continue;
		}
		else
		{
			memoryInfo[i] = (MemoryInfo*)malloc(sizeof(MemoryInfo));

			strcpy_s(memoryInfo[i]->fileName, 128, file);
			memoryInfo[i]->ptr = ptr;
			memoryInfo[i]->size = size;
			memoryInfo[i]->Line = line;

			break;
		}
	}

	return ptr;
}

//----------------------------
// operator new 예외처리
//----------------------------
void operator delete (void* ptr, const char* file, int line)
{}

//---------------------------
// 실제로 사용할 delete
//---------------------------
void operator delete (void* ptr)
{	
	for (int i = 0; i < INFO_COUNT; i++)
	{
		if (memoryInfo[i] == nullptr)
		{
			continue;
		}

		if (memoryInfo[i]->ptr != ptr)
		{
			continue;
		}

		free(memoryInfo[i]);
		free(ptr);
		memoryInfo[i] = nullptr;
	}

	char cBuffer[128];
	sprintf(cBuffer, "NOALLOC [%p] \n", ptr);

	FILE* fp = nullptr;
	fopen_s(&fp, memoryLick.fileName, "at");
	if (fp == nullptr)
	{
		puts("파일을 열 수 없습니다");
		return;
	}

	fwrite(cBuffer, strlen(cBuffer), 1, fp);
	fclose(fp);
}

//---------------------------
// Memory Leak
//---------------------------
CMemoryLick::~CMemoryLick()
{
	FILE* fp = nullptr;

	fopen_s(&fp,memoryLick.fileName, "at");
	if (fp == nullptr)
	{
		puts("파일을 열 수 없습니다");
		return;
	}

	for (int i = 0; i < INFO_COUNT; i++)
	{
		if (memoryInfo[i] == nullptr)
		{
			continue;
		}
		else
		{
			char cBuffer[256];
			sprintf(cBuffer, "LEAK    [%p] [     %d] %s : %d \n", memoryInfo[i]->ptr, memoryInfo[i]->size,
				memoryInfo[i]->fileName, memoryInfo[i]->Line);
			fwrite(cBuffer, strlen(cBuffer), 1, fp);
		}
	}

	fclose(fp);
}