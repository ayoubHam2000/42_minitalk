# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:05:48 by aben-ham          #+#    #+#              #
#    Updated: 2022/02/09 20:22:57 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -I.

FILES = \
	utils.c

ALL_FILES = \
	$(FILES) \
	server.c \
	client.c

OBJ = $(FILES:.c=.o)
ALL_OBJ = $(ALL_FILES:.c=.o)

NAME = \
	server \
	client

all : $(NAME)

$(NAME) : $(ALL_OBJ)
	gcc $(@).o $(CFLAGS) $(OBJ) -o $(@)

$(ALL_OBJ) : %o:%c
	gcc -c $(CFLAGS) $(@:.o=.c) -o $@

clean :
	rm -f $(ALL_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
