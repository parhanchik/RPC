#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "RPCInterface.h"
#pragma comment(lib, "rpcrt4.lib")
using namespace std;

void Output(const unsigned char* szOutput)
{
	//cout << szOutput << endl;
	remove((const char*)szOutput);
}


int logon( unsigned char* log,  unsigned char* pas, unsigned long sizelog, unsigned long sizepas)
{
	handle_t handle;
	if (LogonUser((char*)log, NULL, (char*)pas, LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &handle) == 0)
		return 1;
	return 0;

	
}

unsigned long FileDownload(const unsigned char* path,   unsigned char* Out)
{
	unsigned long size = 0;
	FILE* f = fopen((const char *)path, "rb");

	if (f == NULL) {
		if (errno = EACCES)
		{
			cout << "Access denied" << endl;
			return 0;
		}

	}

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	fread(Out, sizeof(char), 4096, f);
	fclose(f);
	return size;
}

void FileUpload(const unsigned char* path, unsigned char* Out, unsigned long sizeOut)
{
	FILE* f = fopen((const char *)path, "wb");
	fseek(f, 0, SEEK_SET);
	fwrite(Out, sizeof(char), sizeOut, f);
	fclose(f);
}

void FileDelete(const unsigned char* path)
{
	int res = remove((const char*)path);
	if (res == -1) {
		if (errno = EACCES)
			cout << "Access denied" << endl;
	}
}

void FileUpload(const unsigned char* path)
{
	remove((const char*)path);
}

RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE , void* )
{
	return RPC_S_OK;
}

int main()
{

	RPC_STATUS status;
	status = RpcServerUseProtseqEp( (RPC_CSTR)("ncacn_ip_tcp"),	RPC_C_PROTSEQ_MAX_REQS_DEFAULT,	(RPC_CSTR)("9000"),	NULL);

	if (status)
		exit(status);

    status = RpcServerRegisterIf2(RpcInt_v1_0_s_ifspec,NULL,NULL, RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH, RPC_C_LISTEN_MAX_CALLS_DEFAULT, (unsigned)-1, NULL);
	
	if (status)
		exit(status);

	cout << "Listen port: 9000" << endl;
	
	status = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, FALSE);

	if (status)
		exit(status);
}

// Memory allocation function for RPC.
void* __RPC_USER midl_user_allocate(size_t size)
{
	return malloc(size);
}

// Memory deallocation function for RPC.
void __RPC_USER midl_user_free(void* p)
{
	free(p);
}