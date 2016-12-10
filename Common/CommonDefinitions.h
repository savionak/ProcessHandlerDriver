#pragma once

// DeviceName and IOCTL codes to access driver from usermode

#define DRIVER_NAME "ProcessHandlerKmdf"
#define DRIVER_NAME_W L"ProcessHandlerKmdf"

#define DEVICE_NAME_W DRIVER_NAME_W
#define SYS_DEVICE_NAME_W L"PROC_HANDLER_KMDF"

#ifdef __DRIVER_PART__
	// Driver Debug print with prefix
	#define PRINT_DEBUG(x) DbgPrint("\n*** " DRIVER_NAME ": "x);
	#define PRINT_ERROR(x) DbgPrint("\n*** " DRIVER_NAME " !!! ERROR: " x);

	// Symbolic link and device name to register
	#define	SYM_LINK_REG_NAME_W L"\\DosDevices\\" DEVICE_NAME_W
	#define	SYS_DEVICE_REG_NAME_W L"\\Device\\" SYS_DEVICE_NAME_W
#endif
