# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 10:23:27 by nsaraiva          #+#    #+#              #
#    Updated: 2025/08/02 00:56:13 by nsaraiva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = fdf.c fdf_map.c ft_math.c fdf_utils.c ft_rotation.c ft_bresenham.c ft_hook.c ft_display_image.c ft_atoi_base.c
OBJ =  $(SRC:.c=.o)

LIBFT = libft/
GNL = get_next_line/
MLX = minilibx-linux/

LIBFT_A = $(addprefix $(LIBFT), libft.a)
GNL_A = $(addprefix $(GNL), libget.a)
MLX_A = $(addprefix $(MLX), libmlx.a)

CC = cc
CCFLAGS = -Wall -Wextra -Werror -pg -g
INCLUDE = -Iminilibx-linux -I/user/lib -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -O2 -march=native -ffast-math -funroll-loops
LIBRARIES = -L$(LIBFT) -lft -L$(GNL) -lget 
NAME = fdf

all : $(NAME) 

$(NAME) : $(SRC) $(LIBFT_A) $(GNL_A) $(MLX_A)
	$(CC) $(CCFLAGS) $(SRC) $(INCLUDE) $(LIBRARIES) -o $(NAME) -g

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

$(GNL_A):
	$(MAKE) -C $(GNL)

$(MLX_A):
	$(MAKE) CC=clang -s  -C $(MLX)

clean:
	rm -rf $(OBJ) gmon.out
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(GNL)
	$(MAKE) clean -C $(MLX)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) fclean -C $(GNL)

re: fclean all

.PHONY: all clean fclean re
