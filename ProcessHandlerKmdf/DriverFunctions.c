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
	PIO_STACK_LOCATION pIrStack = IoGetCurrentIrpStackLocation(pIrp);

	UNREFERENCED_PARAMETER(pDeviceObj);
	UNREFERENCED_PARAMETER(pIrStack);

	// TODO

#ifdef DBG
	PRINT_DEBUG("Complite ReadWrite dispatch routine");
#endif
	CompleteIrp(pIrp, status, 0);
	return status;
}


NTSTATUS DispatchCreateClose(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp) {
#ifdef DBG
	PRINT_DEBUG("CreateClose dispatch routine");
#endif
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrStack = IoGetCurrentIrpStackLocation(pIrp);

	UNREFERENCED_PARAMETER(pDeviceObj);
	UNREFERENCED_PARAMETER(pIrStack);

	// TODO 

#ifdef DBG
	PRINT_DEBUG("Complite CreateClose dispatch routine");
#endif
	CompleteIrp(pIrp, status, 0);
	return status;
}


NTSTATUS DeviceControlRoutine(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp) {
#ifdef DBG
	PRINT_DEBUG("DeviceControl dispatch routine");
#endif
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrStack = IoGetCurrentIrpStackLocation(pIrp);
	UNREFERENCED_PARAMETER(pIrStack);

	UNREFERENCED_PARAMETER(pDeviceObj);

	// TODO

#ifdef DBG
	PRINT_DEBUG("Complite DeviceControl dispatch routine");
#endif
	CompleteIrp(pIrp, status, 0);
	return status;
}
