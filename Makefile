# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:05:48 by aben-ham          #+#    #+#              #
#    Updated: 2021/12/22 13:57:01 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SNAME = server.out
CNAME = client.out
FLAGS = -Wall -Wextra -Werror -I.
FILES = utils.c\
		client_list.c\
		hamming_code/hamming.a

all:
	$(MAKE) -C hamming_code
	gcc $(FLAGS) server.c $(FILES) -o $(SNAME)
	gcc $(FLAGS) client.c $(FILES) -o $(CNAME)

clean:
	$(MAKE) clean -C ./hamming_code

fclean: clean
	$(MAKE) fclean -C ./hamming_code
	rm $(SNAME) $(CNAME)

re: fclean all
