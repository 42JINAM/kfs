#include "../kernel.h"

int printk(const char *format, ...)
{
    va_list ap;
    int len;

    va_start(ap, format);
    len = vprintf_internal(format, ap);
    va_end(ap);

    return len;
}