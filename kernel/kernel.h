/**
 * Copyright Luke A.C.A. Rieff 2020 all rights reserved. ( Project LukeOS )
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include "../std/types.h"
#include "modules/graphics/framebuffer.h"
#include "modules/serial/serial.h"

/**
 * Gets called by the bootloader after initialization
 */
extern "C" void __attribute__ (( noreturn )) __kernel_entry(void);

#endif
