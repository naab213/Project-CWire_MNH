# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11 -Iinclude -g

# Libraries
LIBS = -lncursesw

# Source files
SRC = main.c tree.c balance.c treatment.c track.c
# Object files
OBJ = $(SRC:.c=.o)

# Executable
TARGET = MNH_CWire

# Linking the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Default target
all: $(TARGET)
	./$(TARGET) $(ARGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)