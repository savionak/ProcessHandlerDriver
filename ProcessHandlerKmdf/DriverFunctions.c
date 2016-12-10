#include "DriverFunctions.h"

// Irp Complition function
NTSTATUS CompleteIrp(PIRP Irp, NTSTATUS status, ULONG info)
{
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}


// Major driver functions to register in DriverEntry

NTSTATUS DispatchReadWrite(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp) {
#ifdef DBG
	PRINT_DEBUG("ReadWrite dispatch routine");
#endif
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

	UNREFERENCED_PARAMETER(pDeviceObj);
	UNREFERENCED_PARAMETER(pIrpStack);

	// TODO

#ifdef DBG
	PRINT_DEBUG("Complite ReadWrite dispatch routine\n");
#endif
	CompleteIrp(pIrp, status, 0);
	return status;
}


NTSTATUS DispatchCreateClose(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp) {
#ifdef DBG
	PRINT_DEBUG("CreateClose dispatch routine");
#endif
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

	UNREFERENCED_PARAMETER(pDeviceObj);
	
#ifdef DBG
	PRINT_DEBUG("File ");
	PUNICODE_STRING pUstr = &(pIrpStack->FileObject->FileName);
	DbgPrint("%wZ ", pUstr);
//	DbgPrint("%.*ws", pUstr->Length / sizeof(WCHAR), pUstr);
#endif

	ULONG info = FILE_EXISTS;
	if ((pIrp->Flags & IRP_CREATE_OPERATION) == IRP_CREATE_OPERATION)
	{
#ifdef DBG
		DbgPrint(" opened.");
#endif
		info = FILE_OPENED;
	}
	else if ((pIrp->Flags & IRP_CLOSE_OPERATION) == IRP_CLOSE_OPERATION)
	{
#ifdef DBG
		DbgPrint(" closed.");
#endif
		status = STATUS_FILE_CLOSED;
	}


	// TODO 

#ifdef DBG
	PRINT_DEBUG("Complite CreateClose dispatch routine\n");
#endif
	CompleteIrp(pIrp, status, info);
	return status;
}


NTSTATUS DeviceControlRoutine(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp) {
#ifdef DBG
	PRINT_DEBUG("DeviceControl dispatch routine");
#endif
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(pIrp);
	UNREFERENCED_PARAMETER(pIrpStack);

	UNREFERENCED_PARAMETER(pDeviceObj);

	// TODO

#ifdef DBG
	PRINT_DEBUG("Complite DeviceControl dispatch routine\n");
#endif
	CompleteIrp(pIrp, status, 0);
	return status;
}
