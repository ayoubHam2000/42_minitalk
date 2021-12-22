# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:05:48 by aben-ham          #+#    #+#              #
#    Updated: 2021/12/22 16:12:47 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -I.
FILES_EX = utils.c
SNAME = server
CNAME = client

all:
	gcc $(CFLAGS) server.c $(FILES_EX) -o $(SNAME)
	gcc $(CFLAGS) client.c $(FILES_EX) -o $(CNAME)

fclean:
	rm $(SNAME) $(CNAME)

re : fclean all
