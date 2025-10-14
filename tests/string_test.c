
#include "string.h"
#include "unistd.h" 

int main(void) {
    char buf[64];
    char tmp[16];

    strcpy(buf, "hello");
    if (strcmp(buf, "hello") != 0) return 1;
    if (strlen(buf) != 5) return 1;

    strcat(buf, " world");
    if (strcmp(buf, "hello world") != 0) return 1;
    if (strlen(buf) != 11) return 1;

    strncpy(tmp, buf, 5);
    tmp[5] = '\0';
    if (strcmp(tmp, "hello") != 0) return 1;

    if (memcmp(buf, "hello world", 11) != 0) return 1;

    if (!memchr(buf, 'w', 11)) return 1;
    if (!strchr(buf, 'h')) return 1;
    if (!strrchr(buf, 'l')) return 1;

    const char msg[] = "string_test: OK\n";
    write(1, msg, sizeof(msg) - 1);

    return 0;
}
