#include "StdAfx.h"
#include "CSPUtil.h"
#pragma comment(lib, "crypt32.lib")

CCSPUtil::CCSPUtil(void)
{
	this->count = 0;
	DWORD dwIndex = 0;
	DWORD dwProvType;
	DWORD cbName;
	while(CryptEnumProviderTypes(dwIndex,NULL,0,&dwProvType,NULL,&cbName)){
		dwIndex++;
	}
	this->iProviderTypeCount=dwIndex;
	dwIndex = 0;
	while(CryptEnumProviders(dwIndex,NULL,0,&dwProvType,NULL,&cbName)){
		dwIndex++;
	}
	this->iProviderCount=dwIndex;
}

CCSPUtil::~CCSPUtil(void)
{
}
int CCSPUtil::GetProviderTypes(char *provider,DWORD index, DWORD *size)
{
	DWORD dwIndex = 0;
	DWORD dwFlags = 0;
	DWORD dwProvType;
	DWORD cbName;
	if(index>this->iProviderTypeCount){
		return 1001;//index out of bound;
	}
	if(provider==NULL){
		CryptEnumProviderTypes(index,NULL,dwFlags,&dwProvType,NULL,&cbName);
		*size = cbName;
		return 1;
	}else{
		CryptEnumProviderTypes(index,NULL,dwFlags,&dwProvType,provider,&cbName);
		return 1;
	}
	return 0;
}
int CCSPUtil::GetProvider(char* provider,int index,int* size)
{
	if(index>this->iProviderCount){
		return 1001;//index out of bound;
	}
	DWORD dwIndex = 0;
	DWORD dwFlags = 0;
	DWORD dwProvType;
	DWORD cbName;

	if(provider==NULL){
		CryptEnumProviders(index,NULL,0,&dwProvType,NULL,&cbName);
		*size = cbName;
		return 1;
	}else{
		CryptEnumProviders(index,NULL,0,&dwProvType,provider,&cbName);
		return 1;
	}
	return 0;
}
int CCSPUtil::ListCertInStore()
{
	HANDLE hStoreHandle;
	hStoreHandle = CertOpenSystemStore(NULL,"MY");
	if(hStoreHandle==NULL){
		return GetLastError();
	}
	PCCERT_CONTEXT certContext = NULL;
	char certName[256];
	while(certContext = CertEnumCertificatesInStore(hStoreHandle,certContext)){
		CertGetNameString(certContext,CERT_NAME_SIMPLE_DISPLAY_TYPE,0,NULL,certName,128);
		printf("%s\r\n",certName);
	}
	if(!CertCloseStore(hStoreHandle, 0)){
		printf("Unable to close the My system store.\n");
		exit(1);
	}
	return 0;
}
int CCSPUtil::AddCertToStore()
{
	HANDLE hStoreHandle;
	hStoreHandle = CertOpenSystemStore(NULL,"MY");
	if(hStoreHandle==NULL){
		return GetLastError();
	}
	PCCERT_CONTEXT certContext = NULL;
	char certName[256];
	certContext = CertEnumCertificatesInStore(hStoreHandle,certContext);
	CertGetNameString(certContext,CERT_NAME_SIMPLE_DISPLAY_TYPE,0,NULL,certName,128);
	printf("%s\r\n",certName);
	BYTE* pbElement;
	DWORD cbSize;
	CertSerializeCertificateStoreElement(certContext,0,NULL,&cbSize);
	pbElement = (BYTE*)malloc(cbSize);
	CertSerializeCertificateStoreElement(certContext,0,pbElement,&cbSize);
	delete pbElement;
	if(!CertCloseStore(hStoreHandle, 0)){
		printf("Unable to close the My store.\n");
		exit(1);
	}
}
