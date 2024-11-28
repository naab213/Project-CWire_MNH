# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11 -Iinclude

# Libraries
LIBS = 

# Source files
SRC = main.c tree.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable
TARGET = MNH_CWire


# Linking the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Default target
all: $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)