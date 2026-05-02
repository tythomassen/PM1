# HW6: Mini Database System - Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g

SRCS = main.c database.c search.c display.c
OBJS = $(SRCS:.c=.o)
HDRS = database.h search.h display.h
TARGET = hw6

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Build with all sanitizers
sanitize: CFLAGS += -fsanitize=address,undefined,leak
sanitize: clean all
	@echo ""
	@echo "Built with AddressSanitizer, UBSan, and LeakSanitizer."

clean:
	rm -f $(OBJS) $(TARGET) students.db

run: $(TARGET)
	./$(TARGET)

# Simple test
test: $(TARGET)
	@echo "Running automated tests..."
	@echo "5" | ./$(TARGET)  # Select sort option
	@echo "Tests complete."

.PHONY: all clean sanitize run test

