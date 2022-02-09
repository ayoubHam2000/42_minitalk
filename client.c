/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/09 19:56:52 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static int	g_bit_index = 0;

static void	send_char(pid_t receiver, char c)
{
	unsigned int	bit;
	int				e;

	while (g_bit_index < 8)
	{
		bit = ((c >> g_bit_index) & 1);
		if (bit)
			e = kill(receiver, SIGUSR1);
		else
			e = kill(receiver, SIGUSR2);
		if (e == -1)
			exit(0);
		pause();
		usleep(WAIT_TIME_C);
	}
	g_bit_index = 0;
}

static void	send_data(pid_t receiver, char *data)
{
	size_t	size;
	size_t	i;
	char	c;

	size = 0;
	while (data[size])
		size++;
	i = 0;
	while (i < size + 9)
	{
		if (i < 8)
		{
			c = *((char *)(&size) + i);
			send_char(receiver, c);
		}
		else
			send_char(receiver, data[i - 8]);
		i++;
	}
}

void	handler(int sig)
{
	static int	n_message;

	if (sig == SIGUSR1)
	{
		g_bit_index++;
		ft_putnbr(n_message);
		write(1, ". Message received\n", 19);
		n_message++;
	}
	else if (sig == SIGUSR2)
	{
		write(1, "Internal Server error!\n", 23);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	if (ac != 3)
		return (0);
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
		return (0);
	if (signal(SIGUSR1, handler) == SIG_ERR
		|| signal(SIGUSR2, handler) == SIG_ERR)
		return (0);
	send_data(server_pid, av[2]);
	return (0);
}
