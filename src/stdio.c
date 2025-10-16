#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


FILE _stdin  = { .fd = 0 };
FILE _stdout = { .fd = 1 };
FILE _stderr = { .fd = 2 };

FILE *stdin  = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

int putchar(int c) {
    char ch = (char)c;
    write(1, &ch, 1);
    return c;
}

int puts(const char *s) {
    size_t len = strlen(s);
    write(1, s, len);
    write(1, "\n", 1);
    return 0;
}

int fputc(int c, FILE *stream) {
    char ch = (char)c;
    write(stream->fd, &ch, 1);
    return c;
}

int fputs(const char *s, FILE *stream) {
    return (int)write(stream->fd, s, strlen(s));
}

int fprintf(FILE *stream, const char *fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    write(stream->fd, buf, strlen(buf));
    return 0;
}

int printf(const char *fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    write(1, buf, strlen(buf));
    return 0;
}

int getchar(void) {
    char c;
    if (read(0, &c, 1) <= 0)
        return EOF;
    return (unsigned char)c;
}

int fclose(FILE *stream) {
    int r = close(stream->fd);
    free(stream);
    return r;
}

FILE *fopen(const char *path, const char *mode) {
    int flags = 0;
    if (strchr(mode, 'r') && strchr(mode, 'w')) flags = 2;
    else if (strchr(mode, 'r')) flags = 0;
    else if (strchr(mode, 'w')) flags = 1;

    int fd = open(path, flags);
    if (fd < 0) return NULL;

    FILE *f = malloc(sizeof(FILE));
    if (!f) return NULL;
    f->fd = fd;
    f->eof = 0;
    f->error = 0;
    return f;
}

int feof(FILE *stream) {
    return stream->eof;
}

int ferror(FILE *stream) {
    return stream->error;
}
