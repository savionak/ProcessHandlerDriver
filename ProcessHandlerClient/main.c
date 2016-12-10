#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#include "..\Common\CommonDefinitions.h"

int _cdecl main(int argc, char* argv[]) {

	int status = EXIT_SUCCESS;

	HANDLE handle = CreateFile(L"\\\\.\\" DEVICE_NAME_W,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		printf("Fail!");
		status = EXIT_FAILURE;
		return status;
	}
	else {
		printf("Okay!");
		getchar();
	}

	// TODO: interact with kernelmode driver via ReadFile and DeviceIoControl

	//CLoseHandle(handle);	// automatically by System

	return status;
}
