#Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS =
TARGET = codeC/exec
SOURCES = ./codeC/main.c ./codeC/tree.c
OBJECTS = $(SOURCES:./%.c=./%.o)
DEPS = ./codeC/settings.h

#Default rule to check if sources have changed
all : $(TARGET)

#Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	chmod +x $(TARGET)
	@echo "Compilation réussie : exécutable généré -> $(TARGET)"

#Rule for building object files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

#Rule to run the program
run: $(TARGET)
	./$(TARGET)

#Rule to clean generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

#Rule to clean only object files
clean-obj:
	rm -f $(OBJECTS)

#Indicates that these rules do not match files
.PHONY: all clean clean-obj run
