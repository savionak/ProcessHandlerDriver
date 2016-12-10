#include "DriverInit.h"

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	NTSTATUS status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(pRegistryPath);

#ifdef DBG
	PRINT_DEBUG("Loading driver...");
#endif

#ifdef DBG
	PRINT_DEBUG("Creating device...");
#endif
	PDEVICE_OBJECT pDeviceObj;

	UNICODE_STRING devName;
	RtlInitUnicodeString(&devName, SYS_DEVICE_REG_NAME_W);

	status = IoCreateDevice(pDriverObject, sizeof(DEVICE_EXTENSION), &devName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDeviceObj);
	if (!NT_SUCCESS(status)) {
#ifdef DBG
		DbgPrint("ERROR!");
		PRINT_ERROR("Failed on creating device.\n");
#endif
		return status;
	}

#ifdef DBG
	DbgPrint("OK");
#endif

	// Create device symbolic link

	// Register major functions

	pDriverObject->DriverUnload = UnloadDriver;

#ifdef DBG
	PRINT_DEBUG("Registering CreateProcessNotifyRoutine...");
#endif

	status = PsSetCreateProcessNotifyRoutine(CreateProcessNotifyRoutine, FALSE);
	if (!NT_SUCCESS(status))
	{
#ifdef DBG
		DbgPrint("ERROR!");
		PRINT_ERROR("Failed on CreateProcessNotifyRoutine registration.\n");
#endif
		return status;
	}

#ifdef DBG
	DbgPrint("OK");
#endif

#ifdef DBG
	PRINT_DEBUG("Driver loaded.\n");
#endif

	return status;
}


VOID UnloadDriver(_In_ PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);

#ifdef DBG
	PRINT_DEBUG("Unloading driver...");
#endif

	// TODO: Clear driver resources

#ifdef DBG
	PRINT_DEBUG("Unregistering CreateProcessNotifyRoutine...");
#endif

	PsSetCreateProcessNotifyRoutine(CreateProcessNotifyRoutine, TRUE);

#ifdef DBG
	PRINT_DEBUG("READY");
#endif

#ifdef DBG
	PRINT_DEBUG("Deleting devices...");
#endif
	PDEVICE_OBJECT pCurrentDevice = pDriverObject->DeviceObject;
	while(pCurrentDevice != NULL) {
		PDEVICE_OBJECT pNextObject = pCurrentDevice->NextDevice;
		IoDeleteDevice(pCurrentDevice);

		pCurrentDevice = pNextObject;
	}

#ifdef DBG
	PRINT_DEBUG("READY");
#endif

#ifdef DBG
	PRINT_DEBUG("Driver unloaded.\n");
#endif
}


VOID CreateProcessNotifyRoutine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId, _In_ BOOLEAN isCreate)
{
	UNREFERENCED_PARAMETER(ParentId);

	PEPROCESS pProcStruct;
	
	NTSTATUS status = PsLookupProcessByProcessId(ProcessId, &pProcStruct);
	if (!NT_SUCCESS(status))
	{
#ifdef DBG
		PRINT_ERROR("Can't obtain process information\n");
#endif
		return;
	}
	
	STRING procName;
	LPCSTR procNameStr = PsGetProcessImageFileName(pProcStruct);

	RtlInitString(&procName, procNameStr);

#ifdef DBG
	PRINT_DEBUG("Process with pid ");
	DbgPrint("%d and name '%s'", ProcessId, procNameStr);
#endif

	if (isCreate == TRUE)
	{
#ifdef DBG
		DbgPrint(" was created\n");
#endif
	}
	else
	{
#ifdef DBG
		DbgPrint(" was terminated\n");
#endif
	}

	// TODO
}
