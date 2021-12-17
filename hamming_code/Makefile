# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 22:59:24 by aben-ham          #+#    #+#              #
#    Updated: 2021/12/17 23:01:57 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = hamming.a
CFLAGS =  -Wall -Wextra -Werror -I. -c
FILES = hamming_code.c\
			hamming_util.c\

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ): $(FILES)
	cc $(CFLAGS) $(FILES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
