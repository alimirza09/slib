CC      = gcc
LD      = ld
AR      = ar

# Flags
CFLAGS      = -ffreestanding -fno-stack-protector -O2 -Wall -Wextra -Iinclude
LDFLAGS     = -m elf_x86_64 -Ttext 0x401000 -e _start --oformat elf64-x86-64

TEST_GCC_FLAGS = -ffreestanding -O2 -Wall -Wextra -Iinclude \
                 -fno-stack-protector -fno-pic -fno-pie -no-pie \
                 -nostdlib -nostartfiles

BUILD   = build
SRC     = src
TESTS   = tests
INCL    = include

LIB_SRCS = crt0.S syscall.S syscalls.c string.c
LIB_OBJS = $(patsubst %.c,$(BUILD)/%.o,$(patsubst %.S,$(BUILD)/%.o,$(LIB_SRCS)))
LIBC_A   = $(BUILD)/libc.a

TEST_SRC = $(TESTS)/hello.c
TEST_OBJ = $(BUILD)/hello.o

TARGET  = hello.elf

all: $(TARGET)

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC)/%.S
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBC_A): $(LIB_OBJS)
	@mkdir -p $(BUILD)
	$(AR) rcs $@ $^

$(BUILD)/hello.o: $(TESTS)/hello.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILD)/crt0.o $(BUILD)/hello.o $(LIBC_A)
	$(LD) $(LDFLAGS) -o $@ $^

$(TESTS)/string_test: $(TESTS)/string_test.c $(LIBC_A) $(BUILD)/crt0.o $(BUILD)/syscall.o $(BUILD)/syscalls.o
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $(TESTS)/string_test.c -o $(BUILD)/string_test.o
	$(CC) $(TEST_GCC_FLAGS) -Iinclude -o $@ \
	    $(BUILD)/string_test.o $(BUILD)/crt0.o $(BUILD)/syscall.o $(BUILD)/syscalls.o $(LIBC_A)

tests/syscall_test:
	$(CC) -ffreestanding -O2 -Wall -Wextra -Iinclude \
	    -fno-stack-protector -fno-pic -fno-pie -no-pie \
	    -nostdlib -nostartfiles \
	    -o tests/syscall_test \
	    tests/syscall_test.c src/syscalls.c src/syscall.S src/crt0.S

clean:
	rm -rf $(BUILD) $(TARGET) tests/syscall_test $(TESTS)/string_test

.PHONY: all clean
