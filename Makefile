# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:05:48 by aben-ham          #+#    #+#              #
#    Updated: 2021/12/22 14:52:54 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES_EX = utils.c

all:
	gcc server.c $(FILES_EX) -o server.out
	gcc client.c $(FILES_EX) -o client.out