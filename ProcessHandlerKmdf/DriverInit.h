#pragma once

#include <ntddk.h>

#include "..\Common\CommonDefinitions.h"
#include "DriverFunctions.h"
#include "Extensions.h"


// Driver initialization
DRIVER_INITIALIZE DriverEntry;

// Process creation and termination callback
VOID SetCreateProcessNotifyRoutine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId, _In_ BOOLEAN isCreate);
