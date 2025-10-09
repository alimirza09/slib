#pragma once

#include <sys/types.h>   

#ifdef __cplusplus
extern "C" {
#endif

ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
void _exit(int status);

#ifdef __cplusplus
}
#endif
