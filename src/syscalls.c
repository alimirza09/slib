#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t open(const char *path, int flags) {
    return syscall(SYS_OPEN, (long)path, flags, 0, 0, 0);
}

ssize_t read(int fd, void *buf, size_t nbytes) {
    return syscall(SYS_READ, fd, (long)buf, nbytes, 0, 0);
}

ssize_t write(int fd, const void *buf, size_t nbytes) {
    return syscall(SYS_WRITE, fd, (long)buf, nbytes, 0, 0);
}

ssize_t close(int fd) {
    return syscall(SYS_CLOSE, fd, 0, 0, 0, 0);
}

ssize_t unlink(const char *path) {
    return syscall(SYS_UNLINK, (long)path, 0, 0, 0, 0);
}

ssize_t mkdir(const char *path) {
    return syscall(SYS_MKDIR, (long)path, 0, 0, 0, 0);
}

ssize_t rmdir(const char *path) {
    return syscall(SYS_RMDIR, (long)path, 0, 0, 0, 0);
}

ssize_t listdir(const char *path, void *buf, size_t bufsize) {
    return syscall(SYS_LISTDIR, (long)path, (long)buf, bufsize, 0, 0);
}

void *mmap(void *addr, size_t length, int flags) {
    return (void *)syscall(SYS_MMAP, (long)addr, length, flags, 0, 0);
}

int munmap(void *addr, size_t length) {
    return syscall(SYS_MUNMAP, (long)addr, length, 0, 0, 0);
}

void *brk(void *addr) {
    return (void *)syscall(SYS_BRK, (long)addr, 0, 0, 0, 0);
}

ssize_t gpu_map(void *user_vaddr){
    return syscall(SYS_GPU_MAP, (long)user_vaddr, 0, 0, 0 ,0);
}

ssize_t gpu_flush(void){
    return syscall(SYS_GPU_FLUSH , 0 ,0 ,0, 0, 0);
}

ssize_t gpu_info(){
    return syscall(SYS_GPU_INFO, 0 ,0 ,0, 0, 0);
}

void _exit(int status) {
    syscall(SYS_EXIT, status, 0, 0, 0, 0);
    for(;;);
}

void exit(int status) {
    _exit(status);
}
