

# Compiler
CC=gcc

#Compiler flags
CFLAGS= -std=c11 -Iinclude

#Libraries
LIBS = -lpthread

#Source files
SRC =src/main.c src/tree.c 

#Object files
OBJ = $(SRC:.c=.o)

#Executable 
TARGET = ./codeC

#Default target
all: $(TARGET)

#Linking the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

test:
	./$(TARGET) -test