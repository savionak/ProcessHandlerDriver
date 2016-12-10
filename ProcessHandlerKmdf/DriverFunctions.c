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

#ifdef DBG
	PRINT_DEBUG("File ");
	PUNICODE_STRING pUstr = &(pIrpStack->FileObject->FileName);
	DbgPrint("%wZ", pUstr);
#endif
	
	ULONG info = FILE_EXISTS;
	
	// TODO: Check for existing "file"

	if (FlagOn(pIrp->Flags, IRP_READ_OPERATION))
	{
#ifdef DBG
		DbgPrint(" is reading.");
#endif
		
		if (pIrpStack->Parameters.Read.Length < READ_BUFFER_SIZE)
		{
#ifdef DBG
			PRINT_ERROR("Invalid buffer size.");
#endif
			status = STATUS_BUFFER_TOO_SMALL;
		}
		else
		{
			READ_BUFFER_TYPE *buf = NULL;
			if (FlagOn(pIrpStack->FileObject->DeviceObject->Flags, DO_BUFFERED_IO))
			{
#ifdef DBG
				PRINT_DEBUG("Buffered I/O");
#endif
				buf = pIrp->AssociatedIrp.SystemBuffer;
			}
			else
			{
#ifdef DBG
				PRINT_ERROR("Unsupported I/O method");
#endif
				status = STATUS_NOT_SUPPORTED;
			}

			if (NT_SUCCESS(status))
			{
				*buf = PsGetCurrentProcessId();
#ifdef DBG
				PRINT_DEBUG("Value ");
				DbgPrint("%ld is read ", *buf);
#endif
			}
		}
	}
	else
	{
#ifdef DBG
		DbgPrint(" operation not supported.");
#endif
		status = STATUS_NOT_SUPPORTED;
	}

#ifdef DBG
	PRINT_DEBUG("Complite ReadWrite dispatch routine\n");
#endif
	CompleteIrp(pIrp, status, info);
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
#endif

	ULONG info = FILE_EXISTS;
	if (FlagOn(pIrp->Flags, IRP_CREATE_OPERATION))
	{
#ifdef DBG
		DbgPrint(" opened.");
#endif
		info = FILE_OPENED;
	}
	else if (FlagOn(pIrp->Flags, IRP_CLOSE_OPERATION))
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
