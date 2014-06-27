#pragma once
#include <windows.h>
#include "stdio.h"
class CCSPUtil
{
private:
	int count;
	int iProviderTypeCount;
	int iProviderCount;
public:
	CCSPUtil(void);
	~CCSPUtil(void);
	int GetProviderTypes(char* provider,DWORD index,DWORD* size);
	int GetProvider(char* provider,int index, int* size);
	int ListCertInStore();
	int AddCertToStore();
};
