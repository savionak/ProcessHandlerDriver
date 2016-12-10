#pragma once

// Driver and Device names

#define DRIVER_NAME "ProcessHandlerKmdf"
#define DRIVER_NAME_W L"ProcessHandlerKmdf"

#define DEVICE_NAME_W DRIVER_NAME_W
#define SYS_DEVICE_NAME_W L"PROC_HANDLER_KMDF"

// Read buffer size
#define READ_BUFFER_TYPE HANDLE
#define READ_BUFFER_SIZE sizeof(READ_BUFFER_TYPE)

// IOCTL codes to access driver from usermode

