#pragma once

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

ssize_t open(const char *path, int flags);
ssize_t read(int fd, void *buf, size_t nbytes);
ssize_t write(int fd, const void *buf, size_t nbytes);
ssize_t close(int fd);
ssize_t unlink(const char *path);
ssize_t mkdir(const char *path);
ssize_t rmdir(const char *path);
ssize_t listdir(const char *path, void *buf, size_t bufsize);

void *mmap(void *addr, size_t length, int flags);
int munmap(void *addr, size_t length);
void *brk(void *addr);

void _exit(int status);
void exit(int status);

#ifdef __cplusplus
}
#endif
