#include "DriverInit.h"

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	NTSTATUS status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(pRegistryPath);

#ifdef DBG
	PRINT_DEBUG("Loading driver...");
#endif

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
		PRINT_ERROR("Failed on CreateProcessNotifyRoutine registration.");
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
	PRINT_DEBUG("OK");
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
		PRINT_ERROR("Can't obtain process information");
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
