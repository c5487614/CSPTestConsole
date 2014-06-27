// CSPTestConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <Wincrypt.h>
#include "CSPUtil.h"
#pragma comment(lib, "advapi32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwIndex = 0;
	DWORD dwFlags = 0;
	DWORD dwProvType;
	DWORD cbName;
	LPTSTR pszName;

	while(CryptEnumProviderTypes(dwIndex,NULL,dwFlags,&dwProvType,NULL,&cbName)){
		pszName = (LPTSTR)malloc(cbName);
		CryptEnumProviderTypes(dwIndex,NULL,dwFlags,&dwProvType,pszName,&cbName);
		printf("%s\r\n",pszName);
		dwIndex++;
		free(pszName);
	}
	CCSPUtil* csputil = new CCSPUtil();
	int size; 
	csputil->GetProvider(NULL,0,&size);
	char* provider = (char*)malloc(size);
	csputil->GetProvider(provider,0,&size);
	printf("%d\r\n",size);
	printf("%s\r\n",provider);

	csputil->ListCertInStore();
	csputil->AddCertToStore();
	int d;
	scanf("%d",&d);
	
	return 0;
}

