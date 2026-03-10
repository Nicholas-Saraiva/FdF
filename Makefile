# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 10:23:27 by nsaraiva          #+#    #+#              #
#    Updated: 2025/08/13 20:04:52 by nsaraiva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors & Symbols
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m
TICK    = [✓]

NAME        = fdf
BUILD_PATH  = .build/

SRC         = fdf.c \
              fdf_utils.c ft_erros.c \
              fdf_map.c ft_map_utils.c \
              ft_atoi_hex.c ft_math_utils.c ft_rotation.c ft_projections.c \
              ft_bresenham.c ft_display_image.c ft_colors.c \
              ft_key_up.c ft_key_down.c ft_mouse_hook.c ft_hooks.c

OBJS        = $(addprefix $(BUILD_PATH), $(notdir $(SRC:.c=.o)))
DEPS        = $(OBJS:.o=.d)

VPATH       = .:utils:srcs/map:srcs/math:srcs/render:srcs/hooks

# Libraries
LIBFT       = include/libft/libft.a
GNL         = include/get_next_line/libget.a
MLX_URL     = https://github.com/42paris/minilibx-linux.git
MLX_DIR     = minilibx-linux
MLX         = minilibx-linux/libmlx.a

CC          = clang
CFLAGS      = -Wall -Wextra -Werror -Iheader -Iminilibx-linux -MMD -MP
LDFLAGS     = -Lminilibx-linux -lmlx -lX11 -lXext -lm -lpthread -O3
LIBRARIES   = -Linclude/libft -lft -Linclude/get_next_line -lget 

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(OBJS)
	@printf "$(YELLOW)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(OBJS) $(LIBRARIES) $(LDFLAGS) -o $(NAME) -g
	@printf "$(GREEN)$(TICK) $(NAME) ready!$(RESET)\n"

$(BUILD_PATH)%.o: %.c | $(BUILD_PATH)
	@printf "$(BLUE)Compiling: $<$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

$(LIBFT):
	@$(MAKE) -s -C include/libft CC=$(CC)

$(GNL):
	@$(MAKE) -s -C include/get_next_line CC=$(CC)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		printf "$(YELLOW)Cloning MiniLibX...$(RESET)\n"; \
		git clone $(MLX_URL) $(MLX_DIR); \
	fi
	@printf "$(YELLOW)Building MiniLibX...$(RESET)\n"
	@$(MAKE) -s -C $(MLX_DIR) CC=$(CC) 2>/dev/null

-include $(DEPS)

clean:
	@rm -rf $(BUILD_PATH)
	@$(MAKE) clean -s -C include/libft
	@$(MAKE) clean -s -C include/get_next_line
	@$(MAKE) clean -s -C minilibx-linux
	@printf "$(BLUE)Objects cleaned.$(RESET)\n"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -s -C include/libft
	@$(MAKE) fclean -s -C include/get_next_line
	@printf "$(BLUE)Executable cleaned.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re