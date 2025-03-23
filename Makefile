# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude

# Detect OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    LDFLAGS = -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else
    LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
endif

# Source files and output
SRC = src/main.c src/new.c
OUT = game.exe

# Build target
all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

# Run the program
run: all
	./$(OUT)

# Clean compiled files
clean:
	rm -f $(OUT)
