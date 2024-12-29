# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS =
TARGET = ../exec
SOURCES = main.c tree.c
OBJECTS = $(SOURCES:.c=.o)
DEPS = settings.h



# Règle pour construire l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	chmod +x $(TARGET)
	@echo "Compilation réussie : exécutable généré -> $(TARGET)"

# Règle pour construire les fichiers objets
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f $(OBJECTS)
	rm -f ../*.csv
	rm -f ../*.png

# Indique que ces règles ne correspondent pas à des fichiers
.PHONY: all clean clean-obj run

