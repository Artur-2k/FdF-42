# EXECUTABLE
TARGET = fdf

# LIBRARIES
LIBFT = libft.a
MINILIBX = libmlx.a
LIBFDF = libfdf.a

# DIRECTORIES
SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/
INC_DIR = inc/

# COMPILE STUFF
CC = gcc
CFLAGS = -I$(INC_DIR) -Ilib/libft -Ilib/minilibx-linux
# -Wall -Werror -Wextra
LINKS = $(LIB_DIR)/$(LIBFT) $(LIB_DIR)/$(MINILIBX) -lX11 -lXext -lm

# FILES
SRC_FILES = animations.c draw.c exit_fdf.c free_matrix.c \
		get_boundaries.c get_matrix.c get_rows_and_cols.c handle_error.c \
		read_keys.c image_utils.c offset.c put_pixel_img.c utils.c\
		resets.c rotations.c scales.c translation.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
MAIN_FILE = $(addprefix $(SRC_DIR), main.c)

# RULES
all: $(TARGET)

$(TARGET): $(LIBFT) $(MINILIBX) $(OBJ)
	@echo "Preparing the executable..."
	@$(CC) $(CFLAGS) -o $@ $(MAIN_FILE) $(OBJ) $(LINKS)
	@echo "\nFdF is ready.\nUsage: ./fdf map_path"

$(LIBFT):
	@echo "Creating libft.a..."
	@make --silent -C $(LIB_DIR)/libft
	@make --silent clean -C $(LIB_DIR)/libft
	@mv $(LIB_DIR)libft/libft.a $(LIB_DIR)

$(MINILIBX):
	@echo "Creating libmlx_Linux.a..."
	@make --silent all -C $(LIB_DIR)/minilibx-linux > /dev/null 2>&1
	@mv $(LIB_DIR)minilibx-linux/libmlx.a $(LIB_DIR)

build:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | build
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning!"
	@rm -rf $(OBJ_DIR) $(LIBFT) $(MINILIBX) $(LIBFDF)

fclean:
	@echo "Full cleaning!"
	@rm -rf $(OBJ_DIR) $(TARGET) $(LIB_DIR)$(LIBFT) $(LIB_DIR)$(MINILIBX)

re: fclean all

.PHONY: all clean fclean re
