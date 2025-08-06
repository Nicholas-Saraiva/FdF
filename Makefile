# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 10:23:27 by nsaraiva          #+#    #+#              #
#    Updated: 2025/08/05 18:19:08 by nsaraiva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = fdf.c
SRC += utils/fdf_utils.c
SRC += srcs/hooks/ft_key_up.c srcs/hooks/ft_key_down.c srcs/hooks/ft_mouse_hook.c srcs/hooks/ft_hooks.c
SRC += srcs/map/fdf_map.c srcs/map/ft_bresenham.c srcs/map/ft_display_image.c srcs/map/ft_colors.c
SRC += srcs/math/ft_atoi_hex.c srcs/math/ft_math_utils.c srcs/math/ft_rotation.c
OBJ =  $(SRC:.c=.o)

LIBFT = include/libft
GNL = include/get_next_line/
MLX = minilibx-linux/

LIBFT_A = $(addprefix $(LIBFT), libft.a)
GNL_A = $(addprefix $(GNL), libget.a)
MLX_A = $(addprefix $(MLX), libmlx.a)

CC = cc
CCFLAGS = -Wall -Wextra -Werror #-pg -g
INCLUDE = -Iminilibx-linux -I/user/lib -Iheader -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm #-O3 -march=native -ffast-math -funroll-loops
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
	$(MAKE) -s -C $(MLX)

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(GNL)
	$(MAKE) clean -C $(MLX)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) fclean -C $(GNL)

re: fclean all

.PHONY: all clean fclean re
