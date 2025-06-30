SRC = fdf.c fdf_utils.c ft_math.c files/get_next_line.c files/get_next_line_utils.c
SRC += files/ft_printf.c files/ft_printf_utils.c \
	  files/ft_char_utils.c files/ft_string_utils.c files/ft_pointer_utils.c \
	  files/ft_decimal_utils.c files/ft_udecimal.c files/ft_hexadecimal.c 
SRC += files/ft_split.c
OBJ =  $(SRC:.c=.o)
CCFLAGS = cc
INCLUDE = -Iminilibx-linux -I/user/lib -Lminilibx-linux -lmlx_Linux -lX11 -lXext
NAME = fdf

all : $(NAME)

$(NAME) : $(SRC)
	$(CCFLAGS) $(SRC) $(INCLUDE) -o $(NAME) -g

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
