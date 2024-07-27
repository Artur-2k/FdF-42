# EXECUTABLE
TARGET = fdf

# LIBRARIES
LIBFT = $(LIB_DIR)libft.a
MINILIBX = $(LIB_DIR)libmlx.a

# DIRECTORIES
SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/
INC_DIR = inc/

# COMPILE STUFF
CC = gcc
CFLAGS = -I$(INC_DIR) -I$(LIB_DIR)libft -I$(LIB_DIR)minilibx-linux -Wall -Werror -Wextra
LINKS = -L$(LIB_DIR) -lft -lmlx -lX11 -lXext -lm

# FILES
SRC_FILES = animations.c draw.c exit_fdf.c free_matrix.c \
	get_boundaries.c get_matrix.c get_rows_and_cols.c handle_error.c \
	read_keys.c image_utils.c offset.c put_pixel_img.c utils.c \
	resets.c rotations.c scales.c translation.c angle_managment.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
MAIN_FILE = $(SRC_DIR)main.c
MAIN_OBJ = $(OBJ_DIR)main.o

# HEADER FILES
HEADERS = $(wildcard $(INC_DIR)*.h)

# RULES
all: $(TARGET)

$(TARGET): $(OBJ) $(MAIN_OBJ) $(LIBFT) $(MINILIBX)
	@echo "Preparing the executable..."
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(MAIN_OBJ) $(LINKS)
	@echo "\nFdF is ready.\nUsage: ./fdf map_path"

$(LIBFT):
	@echo "Creating libft.a..."
	@make --silent -C $(LIB_DIR)libft
	@cp $(LIB_DIR)libft/libft.a $@

$(MINILIBX):
	@echo "Creating libmlx_Linux.a..."
	@make --silent -C $(LIB_DIR)minilibx-linux > /dev/null 2>&1
	@cp $(LIB_DIR)minilibx-linux/libmlx.a $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN_FILE) $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning!"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR)libft clean
	@make -C $(LIB_DIR)minilibx-linux clean

fclean: clean
	@echo "Full cleaning!"
	@rm -f $(TARGET)
	@rm -f $(LIBFT)
	@rm -f $(MINILIBX)
	@make -C $(LIB_DIR)libft fclean

re: fclean all

.PHONY: all clean fclean re