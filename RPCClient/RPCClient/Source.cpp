#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<conio.h>
#include "RPCInterface.h"
using namespace std;

#pragma comment(lib, "rpcrt4.lib")

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 1;

	RPC_STATUS status;
	unsigned char* szStringBinding = NULL;

	const unsigned char keek[] = "C:\\Users\\1\\Desktop\\q.txt";

	status = RpcStringBindingCompose(NULL, (RPC_CSTR)("ncacn_ip_tcp"), (RPC_CSTR)(argv[1]), (RPC_CSTR)(argv[2]), NULL, &szStringBinding);

	if (status)
		exit(status);

	status = RpcBindingFromStringBinding(szStringBinding, &BHandle);

	if (status)
		exit(status);
	
	while (1)
	{
		char log[128] = { 0 };
		char pas[128] = { 0 };
		cout << "login: ";
		cin >> log;
		cout << "password: ";
		cin >> pas;
	

		int res = logon( (unsigned char*)log, (unsigned char*)pas, strlen(log),strlen(pas));

		if (res)
		{
			cout << "LogERROR" << endl<<endl;
		}
		else
		{
			cout << "successful logIN"<<endl;
			break;
		}
	
	}

	while (1)
	{
		char command[64];
		char path[256];
		char out_path[256];
		unsigned char out[4096] = {0};
		unsigned long size;
		char* upl_buf;
		
		cout << "remote@server:~$ ";
		cin >> command;

		if (!strncmp("delete", command, strlen(command) + 1))
		{
			cout << "Enter the path to the file on the remote server: ";
			cin >> path;

			FileDelete((const unsigned char*)path);
		}
		else if (!strncmp("download", command, strlen(command) + 1))
		{
			cout << "Enter the path to the file on the remote server: ";
			cin >> path;
			cout << "Enter the path to the file on the host PC: ";
			cin >> out_path;

			size = FileDownload((const unsigned char*)path, out);
			if (size == 0)
			{
				cout << "Access denied" << endl;
				continue;
			}
			FILE *out_stream = fopen(out_path, "wb");
			fwrite(out, sizeof(char),size, out_stream);
			fclose(out_stream);
		}
		else if (!strncmp("upload", command, strlen(command) + 1))
		{
			cout << "Enter the path to the file on the host PC: ";
			cin >> path;
			cout << "Enter the path to the file on the remote server: ";
			cin >> out_path;

			FILE* f = fopen((const char *)path, "rb");
			fseek(f, 0, SEEK_END);
			size = ftell(f);
			fseek(f, 0, SEEK_SET);
			upl_buf = new char[size];
			fread(upl_buf, sizeof(char), size, f);
			fclose(f);

			FileUpload((const unsigned char*)out_path, (unsigned char*)upl_buf, size);
		}
		else if (!strncmp("exit", command, strlen(command) + 1))
			break;
		
	}

	status = RpcStringFree(&szStringBinding);

	if (status)
		exit(status);

	status = RpcBindingFree(&BHandle);

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