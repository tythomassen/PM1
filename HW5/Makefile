# HW5: Data Structures - Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g

SRCS = main.c functions.c
OBJS = $(SRCS:.c=.o)
TARGET = hw5

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c functions.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build with all sanitizers (REQUIRED for this assignment)
sanitize: CFLAGS += -fsanitize=address,undefined,leak
sanitize: clean all
	@echo ""
	@echo "Built with AddressSanitizer, UBSan, and LeakSanitizer."
	@echo "Run ./hw5 to test for memory errors and leaks."

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean sanitize run

