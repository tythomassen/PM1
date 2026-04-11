# HW4: Structures and File I/O - Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g

SRCS = main.c functions.c
OBJS = $(SRCS:.c=.o)
TARGET = hw4

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c functions.h
	$(CC) $(CFLAGS) -c $< -o $@

sanitize: CFLAGS += -fsanitize=address,undefined
sanitize: clean all

clean:
	rm -f $(OBJS) $(TARGET) students.csv honors.csv contacts.dat sample.log errors.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean sanitize run

