CC = gcc
NASM = nasm

CFLAGS = -Wall -Wextra
LDFLAGS = -lGL -lGLU -lglut -lm

TARGET = test

ASM_SRC = algorithms/midpoint.asm
ASM_OBJ = algorithms/midpoint.o

C_SRC = main.c \
        algorithms/midpoint.c \
        algorithms/brute_force.c \
        algorithms/incremental.c \
        algorithms/incremental_v2.c \
        algorithms/plot.c

$(TARGET): $(ASM_OBJ) $(C_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(C_SRC) $(ASM_OBJ) $(LDFLAGS)

$(ASM_OBJ): $(ASM_SRC)
	$(NASM) -f elf64 $(ASM_SRC) -o $(ASM_OBJ)

clean:
	rm -f $(TARGET) $(ASM_OBJ)