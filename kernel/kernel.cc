/**
 * Copyright Luke A.C.A. Rieff 2020 all rights reserved. ( Project LukeOS )
 */

#include "kernel.h"

/**
 * Gets called by the bootloader after initialization
 */
extern "C" void __attribute__ (( noreturn )) __kernel_entry(void)
{
  modules::graphics::FrameBuffer &fb =modules::graphics::FrameBuffer::get();
  
  fb.setBackground(modules::graphics::FB_BLACK);
  fb.setForeground(modules::graphics::FB_GREEN);
  fb.setRow(3);
  fb.setCol(0);
  fb.writeASCII("Fuck you motherfucker");

  // Configures COM1 ( First Hardware Serial Port )
  modules::serial::COM1.setBaud(SERIAL_BAUD_115200);
  modules::serial::COM1.setLineControl({
    .dlab = 0,
    .break_control = 0,
    .parity = SERIAL_PARITY_NONE,
    .stop_bits = SERIAL_STOPB_1,
    .dl = SERIAL_DL_8BIT
  });
  modules::serial::COM1.setFifoControl({
    .lvl = SERIAL_FIFO_16B_TRIG_14B,
    .bs = 0, .r = 0, .dma = 0,
    .clt = 1,   /* Clear transmission FIFO buffer */
    .clr = 1,   /* Clear receiver FIFO buffer */
    .e = 1      /* Enable FIFO buffer */
  });
  modules::serial::COM1.setModemControl({
    .r = 0, .af = 0, .lb = 0, .ao2 = 0, .ao1 = 0,
    .rts = 1, .dtr = 1
  });

  for (;;);
}
