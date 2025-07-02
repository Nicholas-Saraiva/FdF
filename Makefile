# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 10:23:27 by nsaraiva          #+#    #+#              #
#    Updated: 2025/07/02 10:55:43 by nsaraiva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = fdf.c fdf_utils.c ft_math.c
OBJ =  $(SRC:.c=.o)

LIBFT = libft/
GNL = get_next_line/
PRINTF = ft_printf/
MLX = minilibx-linux/

LIBFT_A = $(addprefix $(LIBFT), libft.a)
GNL_A = $(addprefix $(GNL), libget.a)
PRINTF_A = $(addprefix $(PRINTF), libftprintf.a)
MLX_A = $(addprefix $(MLX), libmlx.a)

CC = cc
CCFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iminilibx-linux -I/user/lib -Lminilibx-linux -lmlx_Linux -lX11 -lXext
LIBRARIES = -L$(LIBFT) -lft -L$(GNL) -lget -L$(PRINTF) -lftprintf
NAME = fdf

all : $(NAME) 

$(NAME) : $(SRC) $(LIBFT_A) $(PRINTF_A) $(GNL_A) $(MLX_A)
	$(CC) $(CCFLAGS) $(SRC) $(INCLUDE) $(LIBRARIES) -o $(NAME) -g

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

$(PRINTF_A):
	$(MAKE) -C $(PRINTF)

$(GNL_A):
	$(MAKE) -C $(GNL)

$(MLX_A):
	$(MAKE) CC=clang -s  -C $(MLX)

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(GNL)
	$(MAKE) clean -C $(MLX)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
