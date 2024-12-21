# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS =
TARGET = exec
SOURCES = main.c tree.c
OBJECTS = $(SOURCES:.c=.o)
DEPS = settings.h

# Règle par défaut pour vérifier si les sources ont changé
.PHONY: all

# Règle pour construire l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	chmod +x $(TARGET)
	@echo "Compilation réussie : exécutable généré -> $(TARGET)"

# Règle pour construire les fichiers objets
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(TARGET)

# Règle pour nettoyer uniquement les fichiers objets
clean-obj:
	rm -f $(OBJECTS)

# Indique que ces règles ne correspondent pas à des fichiers
.PHONY: all clean clean-obj run
