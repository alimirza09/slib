#include <sys/syscall.h>
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count) {
    return syscall(SYS_WRITE, fd, (long)buf, count, 0, 0);
}
