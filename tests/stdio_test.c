#include <stdio.h>

int main(void) {
    printf("stdio test\n");
    puts("Hello from stdio!");
    FILE *f = fopen("TESTFILE.TXT", "rw");
    if (f) {
        fprintf(f, "File I/O OK\n");
        fclose(f);
        puts("File written successfully.");
    } else {
        puts("Failed to open file!");
    }
    return 0;
}
