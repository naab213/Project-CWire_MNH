# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11

# Libraries
LIBS = 

# Source files
SRC = tree.c balance.c treatment.c track.c main.c

# Object files
OBJ = $(SRC:.c=.o)

# Directory executable
TARGET_DIR = codeC

# Executable
TARGET = $(TARGET_DIR)/MNH_CWire

# Linking the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Default target
all: $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)