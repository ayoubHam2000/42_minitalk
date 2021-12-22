/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:36:29 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/22 15:40:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# include <stdio.h>
# include <wchar.h>
# include <locale.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <sys/time.h>

# define WAIT_TIME 50

typedef struct s_client
{
	pid_t			pid;
	unsigned char	res;
	int				bit;
	char			*data;
	size_t			size;
	size_t			i;
}	t_client;

int				get_server_pid(void);
void			share_server_pid(void);
unsigned long	time_micro(void);
char			*git_data_from_file(void);
void			print_bits(char c);

#endif
