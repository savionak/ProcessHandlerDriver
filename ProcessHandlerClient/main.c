#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#include "..\Common\CommonDefinitions.h"

int _cdecl main(int argc, char* argv[]) {

	int status = EXIT_SUCCESS;

	printf("Enter file name: ");

	WCHAR* pfileName = (WCHAR*)malloc(MAX_PATH * sizeof(WCHAR));
	wscanf_s(L"%ws", pfileName);

	WCHAR* pFullName = (WCHAR*)malloc(MAX_PATH * sizeof(WCHAR));
	swprintf_s(pFullName, MAX_PATH, L"\\\\.\\" DEVICE_NAME_W L"\\%ws", pfileName);


	HANDLE handle = CreateFile(pFullName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		printf("Fail!");
		status = EXIT_FAILURE;
	}
	else {
		printf("Okay!");
	}

	// TODO: interact with kernelmode driver via ReadFile and DeviceIoControl

	//CLoseHandle(handle);	// automatically by System

	getchar();
	getchar();

	return status;
}
