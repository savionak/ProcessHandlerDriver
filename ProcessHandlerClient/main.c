#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#include "..\Common\CommonDefinitions.h"

int _cdecl main(int argc, char* argv[]) {

	int status = EXIT_SUCCESS;

	wprintf(L"Enter file name ('%ws' is valid): ", READ_FILE_NAME);

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
	else
	{
		printf("Okay!\n");

		printf("Reading test...");

		READ_BUFFER_TYPE pid;
		DWORD bytesRead = 0;
		BOOL result = ReadFile(handle, &pid, READ_BUFFER_SIZE, &bytesRead, NULL);

		if ((result == TRUE) && (bytesRead == READ_BUFFER_SIZE))
		{
			printf("OK\n");
			printf("DWORD value: %ld", pid);
		}
		else
		{
			printf("FAIL");
			status = EXIT_FAILURE;
		}

		// TODO: interact with kernelmode driver via ReadFile and DeviceIoControl

		//CLoseHandle(handle);	// automatically by System
	}

	getchar();
	getchar();

	return status;
}
