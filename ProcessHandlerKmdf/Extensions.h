#pragma once

// Driver and Device Objects Extension structures


// Pids list entry
typedef struct _TARGETS_LIST_ENTRY {
	LIST_ENTRY listEntry;	// first field, so PLIST_ENTRY === PTARGETS_LIST_ENTRY

	READ_BUFFER_TYPE data;	// must NOT be or contain any pointers (lazy processing)
} TARGETS_LIST_ENTRY, *PTARGETS_LIST_ENTRY;


// DriverObjectExtention
#define CLIENT_ID_ADDR (PVOID)0

typedef struct _DRIVER_EXTENSION_EX {
	STRING targetName;
	LIST_ENTRY targetsList;
	KSPIN_LOCK drvExtSpinLock;
	PIRP pendingIrp;
} DRIVER_EXTENSION_EX, *PDRIVER_EXTENSION_EX;


// DeviceObjectExtension
typedef struct _DEVICE_EXTENSION {
	UNICODE_STRING symLink;
	UNICODE_STRING fileName;
	BOOLEAN isFileOpen;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
