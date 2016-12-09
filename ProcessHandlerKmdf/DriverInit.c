#include "DriverInit.h"

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	NTSTATUS status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(pRegistryPath);

#ifdef DBG
	PRINT_DEBUG("Loading driver...");
#endif

	// Register major functions

	// Register PCREATE_PROCESS_NOTIFY_ROUTINE

	pDriverObject->DriverUnload = UnloadDriver;

#ifdef DBG
	PRINT_DEBUG("Driver loaded.");
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
	PRINT_DEBUG("Driver unloaded.");
#endif
}


VOID SetCreateProcessNotifyRoutine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId, _In_ BOOLEAN isCreate)
{
	UNREFERENCED_PARAMETER(ParentId);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(isCreate);

#ifdef DBG
	PRINT_DEBUG("Some process was created / is about to be terminated");
#endif

	// TODO
}
