#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "..\Common\CommonDefinitions.h"

#include "HandlesMap.h"

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
		printf("ERROR: Can't open driver.\n");
		status = EXIT_FAILURE;
	}
	else
	{
		printf("INFO: Driver opened.\n");

		HandlesMap processMap;

		READ_BUFFER_TYPE data = { 0, FALSE };

		DWORD bytesRead = 0;
		BOOL result = TRUE;

		// TODO: move to separate thread
		while (status != EXIT_FAILURE) {
			result = ReadFile(handle, &data, READ_BUFFER_SIZE, &bytesRead, NULL);

			if ((result == TRUE) && (bytesRead == READ_BUFFER_SIZE))
			{
				if (data.pid == NULL) {
					status = EXIT_FAILURE;

					printf("INFO: Watching stopped.\n");
				}
				else
				{
					printf("INFO: Data received: pid=%ld action=%s\n",
						(long)data.pid,
						data.isCreate ? "Create" : "Terminate"
					);

					if (data.isCreate)
					{
						STARTUPINFO startInfo;
						ZeroMemory(&startInfo, sizeof(STARTUPINFOA));

						PROCESS_INFORMATION procInfo;
						ZeroMemory(&procInfo, sizeof(PROCESS_INFORMATION));

						TCHAR cmdLine[] = CHILD_PROCESS_NAME_W;

						wprintf(L"Command line: '%ws'\n", cmdLine);

						BOOL ok = CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &procInfo);
						if (ok)
						{
							processMap.AddPair(data.pid, procInfo.hProcess);
							printf("INFO: Child process started.\n");
						}
						else
						{
							printf("ERROR: Can't start child process.\n");
						}
					}
					else
					{
						HANDLE child = processMap.PopChildByParent(data.pid);
						if (child != NULL)
						{
							TerminateProcess(child, 0);
							printf("INFO: Child process terminated.\n");
						}
						else
						{
							printf("ERROR: Child process not found.\n");
						}
					}
				}
			}
			else
			{
				//printf("FAILED - buffer is empty");
			}
		}
		
		//CLoseHandle(handle);	// automatically by System
	}

	getchar();

	return status;
}
