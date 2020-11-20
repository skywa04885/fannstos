/**
 * Copyright Luke A.C.A. Rieff 2020 all rights reserved. ( Project LukeOS )
 */

#ifndef _KERNEL_MODULES_SERIAL_SERIAL_H
#define _KERNEL_MODULES_SERIAL_SERIAL_H

#include "../../../std/types.h"
#include "../io.h"

/**************************************************
 * Memory
 **************************************************/

#define SERIAL_COM1_BASE                  0x3F8
#define SERIAL_COM2_BASE                  0x2F8
#define SERIAL_COM3_BASE                  0x3E8
#define SERIAL_COM4_BASE                  0x2E8

#define SERIAL_DATA_REGISTER(A)           (A)
#define SERIAL_INTERRUPT_REGISTER(A)      (A + 1)
#define SERIAL_FIFO_CONTROL_REGISTER(A)   (A + 2)
#define SERIAL_LINE_CONTROL_REGISTER(A)   (A + 3)
#define SERIAL_MODEM_CONTROL_REGISTER(A)  (A + 4)
#define SERIAL_LINE_STATUS_REGISTER(A)    (A + 5)
#define SERIAL_MODEM_STATUS_REGISTER(A)   (A + 6)
#define SERIAL_SCRATCH_REGISTER(A)        (A + 7)

#define SERIAL_DL_8BIT                    0b11
#define SERIAL_DL_7BIT                    0b10
#define SERIAL_DL_6BIT                    0b01
#define SERIAL_DL_5BIT                    0b00

#define SERIAL_STOPB_1                    0b0
#define SERIAL_STOPB_2                    0b1

#define SERIAL_PARITY_NONE                0b000
#define SERIAL_PARITY_ODD                 0b001
#define SERIAL_PARITY_EVEN                0b011
#define SERIAL_PARITY_MARK                0b101
#define SERIAL_PARITY_SPACE               0b111

#define SERIAL_BAUD_115200                1
#define SERIAL_BAUD_57600                 2
#define SERIAL_BAUD_38400                 3
#define SERIAL_BAUD_28800                 4
#define SERIAL_BAUD_23040                 5
#define SERIAL_BAUD_19200                 6
#define SERIAL_BAUD_14400                 8
#define SERIAL_BAUD_12800                 9
#define SERIAL_BAUD_11520                 10
#define SERIAL_BAUD_9600                  12
#define SERIAL_BAUD_7680                  15
#define SERIAL_BAUD_7200                  16
#define SERIAL_BAUD_6400                  18
#define SERIAL_BAUD_5760                  20
#define SERIAL_BAUD_4800                  24

#define SERIAL_FIFO_64B_TRIG_1B           0b00
#define SERIAL_FIFO_64B_TRIG_16B          0b01
#define SERIAL_FIFO_64B_TRIG_32B          0b10
#define SERIAL_FIFO_64B_TRIG_56B          0b11

#define SERIAL_FIFO_16B_TRIG_1B           0b00
#define SERIAL_FIFO_16B_TRIG_4B           0b01
#define SERIAL_FIFO_16B_TRIG_8B           0b10
#define SERIAL_FIFO_16B_TRIG_14B          0b11

namespace modules::serial
{
  typedef struct __attribute__ (( packed ))
  {
    unsigned dlab           : 1;
    unsigned break_control  : 1;
    unsigned parity         : 3;
    unsigned stop_bits      : 1;
    unsigned dl             : 2;
  } serial_line_control_t;

  typedef struct __attribute__ (( packed ))
  {
    unsigned lvl  : 2;
    unsigned bs   : 1;
    unsigned r    : 1;
    unsigned dma  : 1;
    unsigned clt  : 1;
    unsigned clr  : 1;
    unsigned e    : 1;  
  } serial_fifo_control_t;

  typedef struct __attribute__ (( packed ))
  {
    unsigned r    : 2;
    unsigned af   : 1;
    unsigned lb   : 1;
    unsigned ao2  : 1;
    unsigned ao1  : 1;
    unsigned rts  : 1;
    unsigned dtr  : 1;
  } serial_modem_control_t;

  typedef struct __attribute__ (( packed ))
  {
    unsigned rfe : 1; /* Error in Received FIFO */
    unsigned edhr : 1; /* Empty Data Holding Registers */
    unsigned ethr : 1; /* Empty Transmitter Holding Register */
    unsigned bi : 1;
    unsigned fe : 1;
  } serial_fifo_status_t;

  template <u16 A>
  class Serial
  {
  public:
    /**************************************************
     * Control registers
     **************************************************/

    [[ maybe_unused ]] void setBaud(u16 div) noexcept
    {
      this->setLineControl({
        .dlab = 1
      });

      __outb(SERIAL_DATA_REGISTER(A), (div & 0xFF00) >> 8);
      __outb(SERIAL_DATA_REGISTER(A), div);
    }

    [[ maybe_unused ]] void setLineControl(serial_line_control_t cfg) noexcept
    { __outb(SERIAL_LINE_CONTROL_REGISTER(A), *((u8 *) &cfg)); }

    [[ maybe_unused ]] void setFifoControl(serial_fifo_control_t cfg) noexcept
    { __outb(SERIAL_FIFO_CONTROL_REGISTER(A), *((u8 *) &cfg)); }

    [[ maybe_unused ]] void setModemControl(serial_modem_control_t cfg) noexcept
    { __outb(SERIAL_MODEM_CONTROL_REGISTER(A), *((u8 *) &cfg)); }

    /**************************************************
     * Status registers
     **************************************************/

    [[ maybe_unused ]] [[ nodiscard ]] inline serial_fifo_status_t() noexcept
    {
      serial_fifo_status_t res;
      *((u8 *) &res) = __inb(SERIAL_LINE_STATUS_REGISTER(A));
      return res;
    }
  private:
  };

  [[ maybe_unused ]] static Serial<SERIAL_COM1_BASE> COM1;
  [[ maybe_unused ]] static Serial<SERIAL_COM2_BASE> COM2;
  [[ maybe_unused ]] static Serial<SERIAL_COM3_BASE> COM3;
  [[ maybe_unused ]] static Serial<SERIAL_COM4_BASE> COM4;
}

#endif
