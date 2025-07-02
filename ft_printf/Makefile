# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 11:38:26 by nsaraiva          #+#    #+#              #
#    Updated: 2025/07/02 10:48:57 by nsaraiva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = ft_printf.c ft_printf_utils.c \
	  ft_char_utils.c ft_string_utils.c ft_pointer_utils.c \
	  ft_decimal_utils.c ft_udecimal.c ft_hexadecimal.c 

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

all : $(NAME)

$(NAME) : $(OBJ) 
	ar -rcs $(NAME) $(OBJ)	
$(OBJ) : $(SRC)
	cc -c -Wall -Wextra -Werror $(SRC)	

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
