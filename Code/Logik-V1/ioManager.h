#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_
#include <stddef.h>
#include <inttypes.h>
#include "modbus.h"
#include "modbus-tcp.h"

#ifdef __cplusplus
extern "C" {
#endif

//MEMORY MAPPING
//only read address(DI)
#define DI0     0x0000
#define DI1     0x0001
#define DI2     0x0002
#define DI3     0x0003
#define DI4     0x0004
#define DI5     0x0005
#define DI6     0x0006
#define DI7     0x0007
#define DI8     0x0008
#define DI9     0x0009
#define DI10    0x000A
#define DI11    0x000B

//read and write address(DO)
#define DO0     0x0000
#define DO1     0x0001
#define DO2     0x0002
#define DO3     0x0003
#define DO4     0x0004
#define DO5     0x0005
#define DO6     0x0006
#define DO7     0x0007


int open_modbus_tcp_powermang(const char *ip_address, int port);
void close_modbus_tcp_powermang();
int read_DO(int index);
int write_DO(int index, int status);
int read_DI(int index);
int mytest();

#ifdef __cplusplus
}
#endif
#endif
