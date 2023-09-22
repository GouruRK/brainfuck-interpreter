CC=gcc
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
INCLUDE=-I$(INC_DIR)
CFLAGS= -Wall -std=c17

EXEC=brainfuck

SOURCES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(INC_DIR)/*.h)

# On récupère tous les fichiers sources .c, et on leurs préfixe
# le chemin de build, et suffixe en .o :
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
#$(info $(OBJS))

all: $(EXEC)

# Assemblage de l'exécutable final
$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Création des fichiers objets à partir des fichiers sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)
