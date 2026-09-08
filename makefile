CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Isrc/algorithms

LDFLAGS = -lGL -lGLU -lglut -lm

TARGET = proyecto0

SOURCES = \
	src/main.c \
	src/algorithms/brute_force.c \
	src/algorithms/incremental.c \
	src/algorithms/incremental_v2.c \
	src/algorithms/midpoint.c \
	src/algorithms/plot.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean