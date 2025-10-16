CC      = gcc
LD      = ld
AR      = ar

CFLAGS  = -ffreestanding -fno-stack-protector -O2 -Wall -Wextra -Iinclude
LDFLAGS = -m elf_x86_64 -Ttext 0x401000 -e _start --oformat elf64-x86-64

BUILD   = build
SRC     = src
TESTS   = tests
TARGET  = hello.elf

LIB_SRCS = crt0.S syscall.S syscalls.c string.c stdio.c stdlib.c vsprintf.c
LIB_OBJS = $(patsubst %.c,$(BUILD)/%.o,$(patsubst %.S,$(BUILD)/%.o,$(LIB_SRCS)))
LIBC_A   = $(BUILD)/libc.a

TEST_SRC = $(TESTS)/hello.c
TEST_OBJ = $(BUILD)/hello.o

all: $(TARGET)

# Compile C sources
$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble .S sources
$(BUILD)/%.o: $(SRC)/%.S
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Build the static library
$(LIBC_A): $(LIB_OBJS)
	@mkdir -p $(BUILD)
	$(AR) rcs $@ $^

# Build hello.o
$(BUILD)/hello.o: $(TESTS)/hello.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILD)/crt0.o $(BUILD)/hello.o $(LIBC_A)
	$(LD) $(LDFLAGS) -o $@ $^

$(TESTS)/stdio_test: $(TESTS)/stdio_test.c $(LIBC_A)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -nostdlib -nostartfiles -o $@ $^

clean:
	rm -rf $(BUILD) $(TARGET) $(TESTS)/*_test

.PHONY: all clean
