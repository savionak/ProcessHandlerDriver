#include "DriverFunctions.h"

// Irp Complition function
NTSTATUS CompleteIrp(PIRP Irp, NTSTATUS status, ULONG info)
{
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS CompleteReadIrp(PIRP pIrp, READ_BUFFER_TYPE srcBuf)
{
	NTSTATUS status = STATUS_SUCCESS;
	ULONG bytesTrasfered = 0;

#ifdef DBG
	PRINT_DEBUG("Getting last target..");
#endif	

	PMDL mdlAddr = pIrp->MdlAddress;
	READ_BUFFER_TYPE *buf = MmGetSystemAddressForMdlSafe(mdlAddr, LowPagePriority);

	*buf = srcBuf;
	bytesTrasfered = READ_BUFFER_SIZE;

#ifdef DBG
	PRINT_DEBUG("Read IRP Porcessed");
	PRINT_DEBUG("Pid: ");
	DbgPrint("%ld action: %s is read ", buf->pid, buf->isCreate ? "Created" : "Terminated");
#endif

	CompleteIrp(pIrp, status, bytesTrasfered);
	return status;
}


// Major driver functions to register in DriverEntry

NTSTATUS ReadWriteDispatch(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp)
{
#ifdef DBG
	PRINT_DEBUG("ReadWrite dispatch routine");
#endif

	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

#ifdef DBG
	PRINT_DEBUG("File ");
	PUNICODE_STRING pUstr = &(pIrpStack->FileObject->FileName);
	DbgPrint("%wZ", pUstr);
#endif
	
	if (!FlagOn(pIrp->Flags, IRP_READ_OPERATION))
	{
#ifdef DBG
		DbgPrint(" operation not supported.");
#endif
		return STATUS_NOT_SUPPORTED;
	}


#ifdef DBG
	DbgPrint(" is reading.");
#endif
		
	if (pIrpStack->Parameters.Read.Length < READ_BUFFER_SIZE)
	{
#ifdef DBG
		PRINT_ERROR("Invalid buffer size.");
#endif
		return STATUS_BUFFER_TOO_SMALL;
	}


	PMDL mdlAddr = pIrp->MdlAddress;
	if (mdlAddr == NULL)
	{
#ifdef DBG
		PRINT_ERROR("Empty buffer!");
#endif
		return STATUS_BUFFER_TOO_SMALL;
	}
	

	PDRIVER_EXTENSION_EX pDrvExt = (PDRIVER_EXTENSION_EX)IoGetDriverObjectExtension(pDeviceObj->DriverObject, CLIENT_ID_ADDR);
	PKSPIN_LOCK pSpinLock = &(pDrvExt->targetListAccessSync);

	KIRQL oldIrql;
	KeAcquireSpinLock(pSpinLock, &oldIrql);

	if (!IsListEmpty(&(pDrvExt->targetsList)))
	{
		PLIST_ENTRY targetsList = &(pDrvExt->targetsList);
		PTARGETS_LIST_ENTRY nextTarget = (PTARGETS_LIST_ENTRY)RemoveHeadList(targetsList);

		status = CompleteReadIrp(pIrp, nextTarget->data);

		ExFreePoolWithTag(nextTarget, PH_POOL_TAG);
	}
	else
	{
		IoMarkIrpPending(pIrp);
		pDrvExt->pendingIrp = pIrp;
		status = STATUS_PENDING;
	}

	KeReleaseSpinLock(pSpinLock, oldIrql);

#ifdef DBG
	PRINT_DEBUG("Complite ReadWrite dispatch routine\n");
#endif
	return status;
}


NTSTATUS CreateCloseDispatch(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp)
{
#ifdef DBG
	PRINT_DEBUG("CreateClose dispatch routine");
#endif

	NTSTATUS status = STATUS_SUCCESS;
	ULONG info = FILE_EXISTS;
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

#ifdef DBG
	PRINT_DEBUG("File ");
	PUNICODE_STRING pUstr = &(pIrpStack->FileObject->FileName);
	DbgPrint("%wZ ", pUstr);
#endif

	PDEVICE_EXTENSION pDeviceExt = (PDEVICE_EXTENSION)pDeviceObj->DeviceExtension;

	PUNICODE_STRING readFileName = &(pDeviceExt->fileName);
	PUNICODE_STRING openingFileName = &(pIrpStack->FileObject->FileName);

	BOOLEAN isReadFile = RtlEqualUnicodeString(openingFileName, readFileName, TRUE);
	if (isReadFile)
	{
		if (FlagOn(pIrp->Flags, IRP_CREATE_OPERATION))
		{
			if (!(pDeviceExt->isFileOpen))
			{
				pDeviceExt->isFileOpen = TRUE;
				info = FILE_OPENED;
#ifdef DBG
				DbgPrint(" opened.");
#endif
			}
			else
			{
				status = STATUS_FILE_NOT_AVAILABLE;
#ifdef DBG
				DbgPrint(" is already opened by another program.");
#endif
			}
		}
		else if (FlagOn(pIrp->Flags, IRP_CLOSE_OPERATION))
		{
			pDeviceExt->isFileOpen = FALSE;
			status = STATUS_FILE_CLOSED;
#ifdef DBG
			DbgPrint(" closed.");
#endif
		}
	}
	else
	{
		status = STATUS_FILE_NOT_AVAILABLE;
#ifdef DBG
		DbgPrint(" not found. Reason: Incorrect file name.");
#endif
	}


#ifdef DBG
	PRINT_DEBUG("Complite CreateClose dispatch routine\n");
#endif

	CompleteIrp(pIrp, status, info);
	return status;
}


NTSTATUS DeviceControlDispatch(IN PDEVICE_OBJECT pDeviceObj, IN PIRP pIrp)
{
#ifdef DBG
	PRINT_DEBUG("DeviceControl dispatch routine");
#endif
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

	UNREFERENCED_PARAMETER(pIrpStack);
	UNREFERENCED_PARAMETER(pDeviceObj);

	// TODO: enable / disable

#ifdef DBG
	PRINT_DEBUG("Complite DeviceControl dispatch routine\n");
#endif
	CompleteIrp(pIrp, status, 0);
	return status;
}
