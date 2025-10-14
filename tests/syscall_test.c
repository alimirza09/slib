#include <syscall.h>
#include <unistd.h>

int main() {
    const char *fname = "testfile.txt";
    const char *msg = "hello from syscall test\n";
    char buf[64];

    int fd = open(fname, 1); 
    if (fd < 0) {
        write(1, "open failed\n", 12);
        exit(1);
    }

    write(fd, msg, 22);
    close(fd);

    fd = open(fname, 0); 
    if (fd < 0) {
        write(1, "reopen failed\n", 14);
        exit(1);
    }

    ssize_t n = read(fd, buf, 63);
    if (n < 0) {
        write(1, "read failed\n", 12);
        exit(1);
    }
    buf[n] = 0;

    write(1, "Read back: ", 11);
    write(1, buf, n);

    close(fd);
    // unlink(fname);

    write(1, "\nTest completed successfully\n", 30);
    exit(0);
}
