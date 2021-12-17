/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:36:29 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/17 23:16:27 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_printf/ft_printf.h"
# include "hamming_code/hamming_code.h"

# include <stdio.h>
# include <wchar.h>
# include <locale.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <sys/time.h>

# define UNIT_SIZE 8
# define WAIT_TIME 100

typedef struct s_client
{
	pid_t			pid;
	unsigned char	res;
	unsigned char	bit;
	char			*data;
	size_t			size;
	char			hamming[8];
}	t_client;

typedef struct s_lclient
{
	t_client			*client;
	struct s_lclient	*next;	
}	t_lclient;

int				get_server_pid(void);
void			share_server_pid(void);
unsigned long	time_micro();

t_client	*add_or_find_c(t_lclient **lc, pid_t pid);
t_client	*get_next_c(t_lclient *lc, pid_t pid);
void		remove_client(t_lclient **lc, pid_t pid);
void		print_list(t_lclient *lc);

#endif