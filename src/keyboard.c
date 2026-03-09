#include "kernel.h"

unsigned char scancode_set[128] = {
    [0x01] = KEY_ESC,       [0x02] = '1',           [0x03] = '2',           [0x04] = '3',
    [0x05] = '4',           [0x06] = '5',           [0x07] = '6',           [0x08] = '7',
    [0x09] = '8',           [0x0A] = '9',           [0x0B] = '0',           [0x0C] = '-',
    [0x0D] = '=',           [0x0E] = '\b',          [0x0F] = '\t',          [0x10] = 'q',
    [0x11] = 'w',           [0x12] = 'e',           [0x13] = 'r',           [0x14] = 't',
    [0x15] = 'y',           [0x16] = 'u',           [0x17] = 'i',           [0x18] = 'o',
    [0x19] = 'p',           [0x1A] = '[',           [0x1B] = ']',           [0x1C] = '\n',
    [0x1D] = KEY_LCTRL,     [0x1E] = 'a',           [0x1F] = 's',           [0x20] = 'd',
    [0x21] = 'f',           [0x22] = 'g',           [0x23] = 'h',           [0x24] = 'j',
    [0x25] = 'k',           [0x26] = 'l',           [0x27] = ';',           [0x28] = '\'',
    [0x29] = '`',           [0x2A] = KEY_LSHIFT,    [0x2B] = '\\',          [0x2C] = 'z',
    [0x2D] = 'x',           [0x2E] = 'c',           [0x2F] = 'v',           [0x30] = 'b',
    [0x31] = 'n',           [0x32] = 'm',           [0x33] = ',',           [0x34] = '.',
    [0x35] = '/',           [0x36] = KEY_RSHIFT,    [0x37] = KEY_KP_MUL,    [0x38] = KEY_LALT,      
    [0x39] = ' ',           [0x3A] = KEY_CAPSLOCK,  [0x3B] = KEY_F1,        [0x3C] = KEY_F2,     
    [0x3D] = KEY_F3,        [0x3E] = KEY_F4,        [0x3F] = KEY_F5,        [0x40] = KEY_F6,     
    [0x41] = KEY_F7,        [0x42] = KEY_F8,        [0x43] = KEY_F9,        [0x44] = KEY_F10,
    [0x45] = KEY_NUMLOCK,   [0x46] = KEY_SCROLLLOCK,[0x47] = KEY_KP_7,      [0x48] = KEY_KP_8,   
    [0x49] = KEY_KP_9,      [0x4A] = KEY_KP_MINUS,  [0x4B] = KEY_KP_4,      [0x4C] = KEY_KP_5,   
    [0x4D] = KEY_KP_6,      [0x4E] = KEY_KP_PLUS,   [0x4F] = KEY_KP_1,      [0x50] = KEY_KP_2,   
    [0x51] = KEY_KP_3,      [0x52] = KEY_KP_0,      [0x53] = KEY_KP_DOT,
    [0x57] = KEY_F11,       [0x58] = KEY_F12
};

uint8_t read_keyboard(void) {
    while (!(inb(0x64) & 1)) {} // wait until output buffer full
    return inb(0x60);           // read scancode
}

void keyboard_handler()
{
	while (1) {
        uint8_t scancode = read_keyboard();

        if (scancode & 0x80) {
            // release
        } else {
            // pressed
            unsigned char key = scancode_set[scancode];
            terminal_write_char(key);
        }
    }
}
