#pragma once

// Driver Object Extension structure

typedef struct _DEVICE_EXTENSION {
	UNICODE_STRING symLink;
	BOOLEAN isFileOpen;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
