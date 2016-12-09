#pragma once

// DeviceName and IOCTL codes to access driver from usermode

#define DRIVER_NAME "ProcessHandlerKmdf"
#define DRIVER_NAME_W L"ProcessHandlerKmdf"

#ifdef __DRIVER_PART__
	// Driver Debug print with prefix
	#define PRINT_DEBUG(x) DbgPrint("\n*** " DRIVER_NAME ": "x);
	#define PRINT_ERROR(x) DbgPrint("\n*** " DRIVER_NAME " !!! ERROR: " x);
#endif
