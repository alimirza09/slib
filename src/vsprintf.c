#include <stdarg.h>
#include <stddef.h>
#include <string.h>

static void itoa(unsigned long val, char *buf, int base) {
    char tmp[32];
    const char *digits = "0123456789abcdef";
    int i = 0;
    if (val == 0) {
        buf[0] = '0';
        buf[1] = 0;
        return;
    }
    while (val > 0) {
        tmp[i++] = digits[val % base];
        val /= base;
    }
    for (int j = 0; j < i; j++)
        buf[j] = tmp[i - j - 1];
    buf[i] = 0;
}

int vsnprintf(char *buf, size_t size, const char *fmt, va_list args) {
    char *p = buf;
    const char *end = buf + size - 1;

    for (; *fmt && p < end; fmt++) {
        if (*fmt != '%') {
            *p++ = *fmt;
            continue;
        }
        fmt++;
        if (*fmt == 's') {
            const char *s = va_arg(args, const char *);
            while (*s && p < end) *p++ = *s++;
        } else if (*fmt == 'd' || *fmt == 'i') {
            int v = va_arg(args, int);
            if (v < 0) { *p++ = '-'; v = -v; }
            char tmp[32]; itoa((unsigned long)v, tmp, 10);
            for (char *s = tmp; *s && p < end; s++) *p++ = *s;
        } else if (*fmt == 'x') {
            unsigned v = va_arg(args, unsigned);
            char tmp[32]; itoa(v, tmp, 16);
            for (char *s = tmp; *s && p < end; s++) *p++ = *s;
        } else if (*fmt == 'c') {
            char c = (char)va_arg(args, int);
            *p++ = c;
        } else if (*fmt == '%') {
            *p++ = '%';
        }
    }

    *p = '\0';
    return p - buf;
}
