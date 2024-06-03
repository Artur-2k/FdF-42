# Nome do target
TARGET = fdf
LIBRARY = libfdf.a

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIB_DIR = lib

# Compilador e flags
CC = gcc
# ADICIONAR -Wall -Werror -Wextra
CFLAGS = -I$(INC_DIR)

# Arquivos fonte e objetos
# filter-out remove <padrao> de <elements> neste caso tira a main.c que de todos os elementos e guarda o retorno em SRC_FILES
# wildcard é a funcao que nos permite usar wildcares. neste caso *
# patsubst <padrao> <replacement> <elemets> substitui padro por replacement na lista de elementos
# neste caso está a ir buscar o nome de cada SRC_FILE nos SRC_DIR e a dar-lhe o mesmo nome.o no diretorio OBJ_DIR e faz o mesmo para a main
SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
MAIN_FILE = $(SRC_DIR)/main.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_FILE))

#Linking stuff
# acrescentar -lmlx -lm -lX11 -lXext
LINKS = -L$(LIB_DIR) -lfdf -L$(LIB_DIR)/mlx_linux -lmlx -lX11 -lXext -lm

# Regras
all: $(TARGET)
	@echo "Done!"

# depende da libfdf.a e de main.o
# -L e l vao acrescentar lib_dir aos diretorios onde o linker vai procurar e a libfdf.a respetivamente
$(TARGET): $(LIB_DIR)/$(LIBRARY) $(MAIN_OBJ)
	@echo "Preparing the executable..."
	@$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(LINKS)

#a flag -p vai criar o diretorio pai se este ainda nao existir
$(LIB_DIR)/$(LIBRARY): $(OBJ_FILES)
	@echo "Preparing the library..."
	@mkdir -p $(LIB_DIR)
	@ar rcs $@ $^

#os .o vao ter os mesmos nomes q os .c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Preparing the objects..."
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<


clean:
	@echo "Cleaning!"
	@rm -rf $(OBJ_DIR) $(LIB_DIR)/$(LIBRARY)

fclean:
	@echo "Full cleaning!"
	@rm -rf $(OBJ_DIR) $(TARGET) $(LIB_DIR)/$(LIBRARY)

re: fclean all

.PHONY: all clean fclean re
