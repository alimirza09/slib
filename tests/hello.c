#include <unistd.h>

int main(void) {
    write(1, "Hello from userspace!\n", 23);
    return 0;
}

