# --- Compiler and flags ---
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Istb_image
LDFLAGS = -lm

# Debug flags
DEBUG_CFLAGS = -g -O0 -DDEBUG

# --- Source files and output ---
SRC = src/ASCIIMain.c src/ASCIIImages.c
OBJ = $(SRC:.c=.o)
TARGET = ascii_viewer

# --- Default target ---
all: $(TARGET)

# --- Debug target ---
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: clean $(TARGET)

# --- Link all object files into executable ---
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# --- Compile each .c file into .o ---
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Clean up ---
clean:
	rm -f $(OBJ) $(TARGET)
