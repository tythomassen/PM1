CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11
SANFLAGS = -fsanitize=address,undefined,leak
TARGET  = hw5
SRCS    = main.c functions.c

# default build: strict warnings, no sanitizers
$(TARGET): $(SRCS) functions.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# sanitizer build: catches memory errors, UB, and leaks
sanitize: $(SRCS) functions.h
	$(CC) $(CFLAGS) $(SANFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
