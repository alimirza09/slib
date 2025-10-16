#pragma once

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FILE {
  int fd;
  int flags;
  int eof;
  int error;
  char *buffer;
  size_t bufsize;
  size_t bufpos;
  size_t buflen;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

FILE *fopen(const char *pathname, const char *mode);
int fclose(FILE *stream);
int fflush(FILE *stream);

int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
int getchar(void);
int putchar(int c);
int ungetc(int c, FILE *stream);

char *fgets(char *s, int size, FILE *stream);
int fputs(const char *s, FILE *stream);
int puts(const char *s);
char *gets(char *s);

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
int fgetpos(FILE *stream, long *pos);
int fsetpos(FILE *stream, const long *pos);

int feof(FILE *stream);
int ferror(FILE *stream);
void clearerr(FILE *stream);
void perror(const char *s);

int remove(const char *pathname);
int rename(const char *oldpath, const char *newpath);

#define EOF (-1)
#define BUFSIZ 1024
#define FILENAME_MAX 256

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

#define _F_READ 0x01
#define _F_WRITE 0x02
#define _F_EOF 0x04
#define _F_ERR 0x08

#ifdef __cplusplus
}
#endif
