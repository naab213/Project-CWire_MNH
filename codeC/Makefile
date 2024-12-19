# Nom de l'exécutable
EXEC = MNH_CWire

# Répertoires
SRC_DIR = .
INCLUDE_DIR = ./include

# Fichiers source
SRCS = $(SRC_DIR)/tree.c $(SRC_DIR)/balance.c $(SRC_DIR)/treatment.c $(SRC_DIR)/track.c $(SRC_DIR)/main.c

# Fichiers objets (générés automatiquement)
OBJS = $(SRCS:.c=.o)

# Fichiers d'en-têtes
HEADERS = $(INCLUDE_DIR)/tree.h $(INCLUDE_DIR)/balance.h $(INCLUDE_DIR)/treatment.h $(INCLUDE_DIR)/track.h

# Compilateur et options
CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)  # Options de compilation avec le chemin vers les fichiers d'en-têtes

# Règle par défaut : construire l'exécutable
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Règles pour chaque fichier .o (respect de l'ordre)
$(SRC_DIR)/tree.o: $(SRC_DIR)/tree.c $(INCLUDE_DIR)/tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/balance.o: $(SRC_DIR)/balance.c $(INCLUDE_DIR)/balance.h $(INCLUDE_DIR)/tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/treatment.o: $(SRC_DIR)/treatment.c $(INCLUDE_DIR)/treatment.h $(INCLUDE_DIR)/tree.h $(INCLUDE_DIR)/balance.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/track.o: $(SRC_DIR)/track.c $(INCLUDE_DIR)/track.h $(INCLUDE_DIR)/tree.h $(INCLUDE_DIR)/balance.h $(INCLUDE_DIR)/treatment.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de nettoyage
clean:
	rm -f $(OBJS) $(EXEC)

# Règle pour tout recompiler
rebuild: clean all