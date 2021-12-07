# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:05:48 by aben-ham          #+#    #+#              #
#    Updated: 2021/12/07 21:57:45 by ayoub            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES_EX = utils.c\
		ft_printf/libftprintf.a

all:
	gcc server.c $(FILES_EX) -o server.out
	gcc client.c $(FILES_EX) -o client.out