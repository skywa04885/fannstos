/**
 * Copyright Luke A.C.A. Rieff 2020 all rights reserved. ( Project LukeOS )
 */

#include "framebuffer.h"

namespace modules::graphics
{
  FrameBuffer FrameBuffer::s_Instance;

  FrameBuffer::FrameBuffer() noexcept:
    m_Row(0), m_Col(0)
  {}

  /**************************************************
   * FrameBuffer cursor
   **************************************************/

  /**
   * Moves the cursor to specified position
   * @param pos
   */
  [[ maybe_unused ]] void FrameBuffer::moveCursor(u16 pos) noexcept
  {
    __outb(FRAMEBUFFER_CMD_PORT, FRAMEBUFFER_CMD_CURSOR_HI);
    __outb(FRAMEBUFFER_DATA_PORT, (pos & 0xFF00) >> 8);
    __outb(FRAMEBUFFER_CMD_PORT, FRAMEBUFFER_CMD_CURSOR_LO);
    __outb(FRAMEBUFFER_DATA_PORT, pos);
  }

  /**************************************************
   * FrameBuffer writing
   **************************************************/

  /**
   * Writes an ASCII char to the frame buffer
   * @param char
   */
  [[ maybe_unused ]] void FrameBuffer::writeASCII(char c)
  {
    framebuffer_ascii_char_t t = {
      .ascii = c,
      .foreground = this->m_Foreground,
      .background = this->m_Background
    };

    *((volatile u16 *) FRAMEBUFFER_REGISTER + this->getBufferOffset()) = *((u16 *) &t);
    ++this->m_Col;
  }

  /**
   * Writes an ASCII string to the frame buffer
   * @param string
   */
  [[ maybe_unused ]] void FrameBuffer::writeASCII(const char *string)
  {
    while (*string != '\0') this->writeASCII(*string++);
    this->moveCursor(this->getBufferOffset());
  }
}