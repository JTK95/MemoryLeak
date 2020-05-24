#include "stdafx.h"
#include "mynew.h"

class CManager
{
public:
	CManager()
	{}
	~CManager()
	{}

};

int main()
{
	CManager* ptr = new CManager;

	delete ptr;

	CManager* ptr1 = new CManager;
	CManager* ptr2 = new CManager;
	CManager* ptr3 = new CManager;

	return 0;
}