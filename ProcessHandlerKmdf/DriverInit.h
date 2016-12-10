#pragma once

//#include <ntddk.h>
#include <ntifs.h>

#define __DRIVER_PART__	// to use PRINT_DEBUG macro

#include "..\Common\CommonDefinitions.h"
#include "Extensions.h"
#include "DriverFunctions.h"

// Driver initialization
DRIVER_INITIALIZE DriverEntry;

// Driver deinitialization
DRIVER_UNLOAD UnloadDriver;

// Process creation and termination callback
VOID CreateProcessNotifyRoutine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId, _In_ BOOLEAN isCreate);

// Get process image by PID (undocumented but widely used function)
extern LPCSTR PsGetProcessImageFileName(_In_ PEPROCESS Process);
