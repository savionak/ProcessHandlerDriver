#pragma once

#include "../Common/CommonDefinitions.h"

// Driver Debug print with prefix
#define PRINT_DEBUG(x) DbgPrint("\n*** " DRIVER_NAME ": "x);
#define PRINT_ERROR(x) DbgPrint("\n*** " DRIVER_NAME " !!! ERROR: " x);

// Symbolic link and device name to register
#define	SYM_LINK_REG_NAME_W L"\\DosDevices\\" DEVICE_NAME_W
#define	SYS_DEVICE_REG_NAME_W L"\\Device\\" SYS_DEVICE_NAME_W

// Optional breakpoints (comment to disable)
#define DBG_INIT_BREAK

#define PH_POOL_TAG '1gaT'