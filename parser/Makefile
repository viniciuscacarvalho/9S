CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRC = main.c parser.c command_callbacks.c
OBJ = $(SRC:.c=.o)
DEPS = parser.h parser_codes.h command_callbacks.h
TARGET = main

all: $(TARGET)
	./main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
