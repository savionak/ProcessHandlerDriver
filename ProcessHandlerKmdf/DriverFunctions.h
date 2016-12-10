#pragma once

//#include <ntddk.h>
#include <ntifs.h>

#include "DriverDefs.h"
#include "Extensions.h"

// Major driver functions to register in DriverEntry

// CreateFile dispatcher
DRIVER_DISPATCH DispatchReadWrite;

// CloseHandle dispatcher
DRIVER_DISPATCH DispatchCreateClose;

// DeviceIoControl dispatcher
DRIVER_DISPATCH DeviceControlRoutine;
