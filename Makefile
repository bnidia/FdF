# Manual for Makefile
# https://www.gnu.org/software/make/manual/html_node/index.html
NAME = fdf

SRC = main.c draw.c init_data.c key_and_mouse_controls.c

OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))
D_FILES = $(addprefix $(OBJDIR),$(SRC:.c=.d))
CC ?= gcc -Wall -Werror -Wextra
DEBUG = -g
OPTIMIZATION = -O2
LIB += -lmlx
LIB += -lft
LIB += -lXext #X11 miscellaneous extensions library
LIB += -lX11 #Core X11 protocol client library
LIB += -lm #standard C library of basic mathematical functions
LIB += -lz #libz - compression/decompression library
LIBPATH += -L./libraries/mlx_linux
LIBPATH += -L./libraries/libft
LIBINC += -I./libraries/mlx_linux/
LIBINC += -I./libraries/libft/

all : $(NAME)

$(NAME): obj $(OBJ)
	make -C ./libraries/libft/
	make -C ./libraries/mlx_linux/
	$(CC) $(OBJ) $(LIBPATH) $(LIB) $(LIBINC)  -o $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJ): $(OBJDIR)%.o : %.c fdf.h
	$(CC) $(DEBUG) $(OPTIMIZATION) $(LIBINC) -c $< -o $@ -MMD

include $(wildcard $(D_FILES))

bonus: all

norm:
	norminette $(SRC)

# rule for the cleaning
clean:
	make clean -C ./libraries/libft
	make clean -C ./libraries/mlx_linux
	rm -rf $(OBJDIR)

fclean:
	make fclean -C ./libraries/libft
	make clean -C ./libraries/mlx_linux
	rm -rf $(OBJDIR)
	rm -f $(NAME)

# rule for rebuild a project
re: fclean all

# directory exceptions
.PHONY: all clean fclean norm re bonus
