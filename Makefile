
CC     = gcc
LD     = ld
CFLAGS = -ffreestanding -fno-stack-protector -O2 -Wall -Wextra -Iinclude
LDFLAGS = -m elf_x86_64 -Ttext 0x401000 -e _start --oformat elf64-x86-64

BUILD  = build
SRC    = src
TESTS  = tests

LIBOBJS = $(BUILD)/crt0.o $(BUILD)/syscall.o $(BUILD)/syscalls.o
TESTOBJS = $(BUILD)/hello.o
LIBC_A = $(BUILD)/libc.a
TARGET = hello.elf

all: $(TARGET)

$(BUILD)/crt0.o: $(SRC)/crt0.S
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/syscall.o: $(SRC)/syscall.S
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/syscalls.o: $(SRC)/syscalls.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBC_A): $(LIBOBJS)
	ar rcs $@ $^

$(BUILD)/hello.o: $(TESTS)/hello.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILD)/crt0.o $(BUILD)/hello.o $(LIBC_A)
	$(LD) $(LDFLAGS) -o $@ $^

tests/syscall_test: tests/syscall_test.c src/syscalls.c src/syscall.S
	$(CC) -nostdlib -static -Iinclude -o $@ tests/syscall_test.c src/syscalls.c src/syscall.S

clean:
	rm -rf $(BUILD) $(TARGET)

.PHONY: all clean
