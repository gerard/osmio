#include <stdarg.h>

static char *write_hex(char *str, unsigned int n)
{
    for (int i = 0; i < 2*sizeof(unsigned int); i++) {
        *str++ = (n << 4*i) & 0xF;
    }

    return str;
}

static char *handle_format_char(char *str, char format, va_list *ap)
{
    switch(format) {
    case '%':
        *str++ = '%';
        break;
    case 'h':
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
