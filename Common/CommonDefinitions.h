#pragma once

// Driver and Device names

#define DRIVER_NAME "ProcessHandlerKmdf"
#define DRIVER_NAME_W L"ProcessHandlerKmdf"

#define DEVICE_NAME_W DRIVER_NAME_W
#define SYS_DEVICE_NAME_W L"PROC_HANDLER_KMDF"

// Read buffer file name
#define READ_FILE_NAME L"File00"

typedef struct _DATA_BUFFER {
	HANDLE pid;
	BOOLEAN isCreate;
} DATA_BUFFER;

// Read buffer size
#define READ_BUFFER_TYPE DATA_BUFFER	// must NOT be or contain any pointers (lazy processing)
#define READ_BUFFER_SIZE sizeof(READ_BUFFER_TYPE)

// Target process name
#define TARGET_PROCESS_NAME "calc.exe"

//
#define CHILD_PROCESS_NAME_W L"notepad.exe"

// IOCTL codes to access driver from usermode

