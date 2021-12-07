/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:36:29 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/07 21:52:14 by ayoub            ###   ########.fr       */
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

# define CHUNK_SIZE 30
# define UNIT_SIZE 31
# define WAIT_TIME 20

typedef struct s_client
{
	int		pid;
	char	**data;
	int		size;
}	t_client;

typedef struct s_lclient
{
	t_client	*client;
	s_lclient	*next;	
}	t_lclient;

int		get_server_pid(void);
void	share_server_pid(void);

#endif