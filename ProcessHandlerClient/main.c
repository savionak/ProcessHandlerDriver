#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#include "..\Common\CommonDefinitions.h"

int _cdecl main(int argc, char* argv[]) {

	int status = EXIT_SUCCESS;

	HANDLE handle = CreateFile(L"\\\\.\\" DEVICE_NAME_W L"\\" READ_FILE_NAME,
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

		READ_BUFFER_TYPE data;
		data.pid = 0;
		data.isCreate = FALSE;

		DWORD bytesRead = 0;
		BOOL result = TRUE;
//		while (status != EXIT_FAILURE) {
			result = ReadFile(handle, &data, READ_BUFFER_SIZE, &bytesRead, NULL);

			if ((result == TRUE) )// && (bytesRead == READ_BUFFER_SIZE))
			{
				printf("pid: %ld action: %s",
					data.pid, 
					data.isCreate ? "Create" : "Terminate"
					);
			}
			else
			{
				printf("FAILED - buffer is empty");
			}
//		}
		// TODO: interact with kernelmode driver via ReadFile and DeviceIoControl

		//CLoseHandle(handle);	// automatically by System
	}

//	getchar();
	getchar();

	return status;
}
