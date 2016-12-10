#pragma once

// Driver and Device Objects Extension structure

#define CLIENT_ID_ADDR (PVOID)0

typedef struct _DRIVER_EXTENSION_EX {
	STRING targetName;
	READ_BUFFER_TYPE lastTargetPid;
} DRIVER_EXTENSION_EX, *PDRIVER_EXTENSION_EX;

typedef struct _DEVICE_EXTENSION {
	UNICODE_STRING symLink;
	UNICODE_STRING fileName;
	BOOLEAN isFileOpen;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
