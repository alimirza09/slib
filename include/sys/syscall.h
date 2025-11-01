#pragma once

#define SYS_OPEN        0
#define SYS_READ        1
#define SYS_WRITE       2
#define SYS_CLOSE       3
#define SYS_UNLINK      4
#define SYS_MKDIR       5
#define SYS_RMDIR       6
#define SYS_LISTDIR     7
#define SYS_EXIT        8
#define SYS_MMAP        9
#define SYS_MUNMAP      10
#define SYS_BRK         11
#define SYS_GPU_INFO    12
#define SYS_GPU_MAP     13
#define SYS_GPU_FLUSH   14

long syscall(long num, long arg1, long arg2, long arg3, long arg4, long arg5);
