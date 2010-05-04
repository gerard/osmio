#include "stdarg.h"
#include "console.h"

static char *write_hex(char *str, unsigned int n)
{
    int digit;
    int n_digits = 2 * sizeof(unsigned int);

    *str++ = '0';
    *str++ = 'x';

    for (int i = n_digits - 1; i >= 0; i--) {
        digit = ((n >> 4 * i) & 0xF);
        *str++ = digit < 10 ? digit + 0x30 : digit + 0x37;
    }

    return str;
}

static char *handle_format_char(char *str, char format, va_list *ap)
{
    switch(format) {
    case '%':
        *str++ = '%';
        break;
    case 'x':
        str = write_hex(str, va_arg(*ap, unsigned int));
        break;
    default:
        *str++ = '%';
        *str++ = format;
    }

    return str;
}

int vsprintf(char *str, const char *format, va_list ap)
{
    int i;
    char c;

    for (i = 0; (c = format[i]); i++) {
        switch(c) {
        case '%':
            i++;
            str = handle_format_char(str, format[i], &ap);
            break;
        default:
            *str++ = format[i];
        }
    }

    *str++ = 0;

    /* FIXME: Non-standard return value */
    return 0;
}

int sprintf(char *str, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vsprintf(str, format, ap);
    va_end(ap);
}

int printf(const char *format, ...)
{
    char buffer[128];
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = vsprintf(buffer, format, ap);
    va_end(ap);
    
    console_write(buffer);
    return ret;
}
