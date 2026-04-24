# LogLite Makefile
# Course: Programming Methodology I (Spring 2026)
#
# Usage:
#   make              - Build the loglite executable
#   make clean        - Remove all generated files
#   make sanitize     - Build with AddressSanitizer and UndefinedBehaviorSanitizer
#   make debug        - Build with debug symbols
#
# The autograder will test with:
#   make clean && make
#   make clean && make CFLAGS="..." (with sanitizers)

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g

# Source files
SRCS = main.c parser.c query.c
OBJS = $(SRCS:.c=.o)
HEADERS = types.h parser.h query.h

# Target executable
TARGET = loglite

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Build with sanitizers (for testing memory safety)
sanitize: CFLAGS += -fsanitize=address,undefined
sanitize: clean $(TARGET)

# Build with extra debug info
debug: CFLAGS += -DDEBUG
debug: clean $(TARGET)

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean sanitize debug

