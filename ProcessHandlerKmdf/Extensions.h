#pragma once

// Driver Object Extension structure

typedef struct _DEVICE_EXTENSION {
	UNICODE_STRING symLink;
	UNICODE_STRING fileName;
	BOOLEAN isFileOpen;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
