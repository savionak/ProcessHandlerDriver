#pragma once

//#include <ntddk.h>
#include <ntifs.h>

#include "DriverDefs.h"
#include "Extensions.h"

// Major driver functions to register in DriverEntry

// ReadWrite dispatcher
DRIVER_DISPATCH ReadWriteDispatch;

// CreateFile/CloseHandle dispatcher
DRIVER_DISPATCH CreateCloseDispatch;

// DeviceIoControl dispatcher
DRIVER_DISPATCH DeviceControlDispatch;

// Complete (pending or not) ReadIrp: MUST be called inside synchronized block
NTSTATUS CompleteReadIrp(PIRP pIrp, READ_BUFFER_TYPE srcBuf);
