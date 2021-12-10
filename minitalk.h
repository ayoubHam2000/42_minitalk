/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:36:29 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/11 00:43:50 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_printf/ft_printf.h"

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
# define WAIT_TIME 50

typedef struct s_client
{
	pid_t	pid;
	unsigned char	res;
	unsigned char	bit;
	char	*data;
	size_t	size;
}	t_client;

typedef struct s_lclient
{
	t_client			*client;
	struct s_lclient	*next;	
}	t_lclient;

int			get_server_pid(void);
void		share_server_pid(void);

t_client	*add_or_find_c(t_lclient **lc, pid_t pid);
t_client	*get_next_c(t_lclient *lc, pid_t pid);
void		remove_client(t_lclient **lc, pid_t pid);
void		print_list(t_lclient *lc);

#endif