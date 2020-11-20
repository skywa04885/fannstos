/**
 * Copyright Luke A.C.A. Rieff 2020 all rights reserved. ( Project LukeOS )
 */

#ifndef _KERNEL_MODULES_GRAPHICS_FRAMEBUFFER_H
#define _KERNEL_MODULES_GRAPHICS_FRAMEBUFFER_H

#include "../../../std/types.h"
#include "../io.h"

/**************************************************
 * Memory
 **************************************************/

#define FRAMEBUFFER_CMD_PORT          0x3D4
#define FRAMEBUFFER_DATA_PORT         0x3D5

#define FRAMEBUFFER_REGISTER          0x000B8000

/**************************************************
 * Commands
 **************************************************/

#define FRAMEBUFFER_CMD_CURSOR_HI     14
#define FRAMEBUFFER_CMD_CURSOR_LO     15

/**************************************************
 * Config
 **************************************************/

#define FRAMEBUFFER_MAX_ROWS          50
#define FRAMEBUFFER_MAX_COLS          80

namespace modules::graphics
{
  typedef enum __attribute__ (( packed ))
  {
    FB_BLACK = 0,
    FB_BLUE,
    FB_GREEN,
    FB_CYAN,
    FB_RED,
    FB_MAGENTA,
    FB_BROWN,
    FB_LIGHT_GREY,
    FB_DARK_GREY,
    FB_LIGHT_BLUE,
    FB_LIGHT_GREEN,
    FB_LIGHT_CYAN,
    FB_LIGHT_RED,
    FB_LIGHT_MAGENTA,
    FB_LIGHT_BROWN,
    FB_WHITE
  } framebuffer_color_t;

  typedef struct __attribute__ (( packed ))
  {
    unsigned ascii      : 8;
    unsigned foreground : 4;
    unsigned background : 4;
  } framebuffer_ascii_char_t;

  class FrameBuffer
  {
  public:
    /**************************************************
     * Getters and Setters
     **************************************************/

    /**
     * Returns the framebuffer instance
     * @return instance
     */
    [[ maybe_unused ]] [[ nodiscard ]] static inline FrameBuffer &get() noexcept
    { return FrameBuffer::s_Instance; }

    [[ maybe_unused ]] [[ nodiscard ]] inline u8 getRow() const noexcept
    { return this->m_Row; }

    [[ maybe_unused ]] [[ nodiscard ]] inline u8 getCol() const noexcept
    { return this->m_Col; }

    [[ maybe_unused ]] inline void setCol(u8 col) noexcept
    { this->m_Col = col; }

    [[ maybe_unused ]] inline void setRow(u8 row) noexcept
    { this->m_Row = row; }

    [[ maybe_unused ]] inline void setForeground(framebuffer_color_t color) noexcept
    { this->m_Foreground = color; }

    [[ maybe_unused ]] inline void setBackground(framebuffer_color_t color) noexcept
    { this->m_Background = color; }

    /**************************************************
     * FrameBuffer cursor
     **************************************************/

    /**
     * Moves the cursor to specified position
     * @param pos
     */
    [[ maybe_unused ]] void moveCursor(u16 pos) noexcept;

    /**************************************************
     * FrameBuffer writing
     **************************************************/

    /**
     * Gets the offset in the framebuffer
     * @return offset
     */
    [[ maybe_unused ]] [[ nodiscard ]] inline u16 getBufferOffset()
    { return this->m_Row * FRAMEBUFFER_MAX_COLS + this->m_Col; }

    /**
     * Writes an ASCII char to the frame buffer
     * @param char
     */
    [[ maybe_unused ]] void writeASCII(char c);

    /**
     * Writes an ASCII string to the frame buffer
     * @param string
     */
    [[ maybe_unused ]] void writeASCII(const char *string);
  protected:
    FrameBuffer() noexcept;
    ~FrameBuffer() = default;
  private:
    static FrameBuffer s_Instance;
    u8 m_Row, m_Col;
    framebuffer_color_t m_Background, m_Foreground;
  };
}

#endif
