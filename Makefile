CC = gcc
CFLAGS = -Wall -g -O0

# List all your C source files
SRCS = main.c consolelog.c files.c arguments.c

# List all your Header files to track changes
DEPS = consolelog.h files.h arguments.h

# Automatically converts the .c list into a .o (object) list
OBJS = $(SRCS:.c=.o)

all: main

# Links main.o, consolelog.o, and files.o together
main : $(OBJS)
	$(CC) $^ -o $@

# Compiles each .c file into a .o file, watching for header changes
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o main
