#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include "../../std/types.h"

extern "C" void __outb(u16 port, u8 data);
extern "C" u8 __inb(u16 port);

#endif
