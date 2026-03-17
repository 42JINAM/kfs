#include "../kernel.h"

void hex_to_str(uint32_t value, char *buf)
{
    const char *hex = "0123456789ABCDEF";

    buf[0] = hex[(value >> 4) & 0xF]; // high nibble
    buf[1] = hex[value & 0xF];        // low nibble
    buf[2] = '\0';
}

void print_hex_line(uint32_t addr, int bytes) {
    char buf[3];
    char *c = (char *)addr;

    for (int i = 0; i < 16; i++) {
      if (i < bytes) {
        hex_to_str((uint32_t)c[i], buf);
        printf("%s ", buf);
      } else {
        printf("   ", buf);
      }
    }
}

void print_ascii_line(uint32_t addr, int bytes) {
    for (int i = 0; i < bytes; i++) {
        if (*(char *)addr <= 32)
            printf("%c", '.');
        else
            printf("%c", *(char *)addr);
        addr++;
    }
}

void hexdump(uint32_t addr, int bytes)
{
    if (bytes <= 0)
        return;
    
    int line = bytes / 16;
    int rest = bytes % 16;

    for (int i = 0; i < line; i++) {
        // 1. print address
        printf("%p: ", addr);

        // 2. print hex
        print_hex_line(addr, 16);

        // 3. print ascii
        print_ascii_line(addr, 16);
        printf("\n");
        addr = addr + 16;
    }
    // last line
    printf("%p: ", addr);
    print_hex_line(addr, rest);
    print_ascii_line(addr, rest);
    printf("\n");
}
