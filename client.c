/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/22 16:40:10 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_bit_index = 0;

static void	send_char(pid_t receiver, char c)
{
	unsigned int	bit;
	unsigned int	time_out;
	int				e;

	time_out = TIME_OUT;
	while (g_bit_index < 8)
	{
		bit = ((c >> g_bit_index) & 1);
		if (bit)
			e = kill(receiver, SIGUSR1);
		else
			e = kill(receiver, SIGUSR2);
		if (e == -1)
			exit(0);
		usleep(WAIT_TIME_C);
		time_out = time_out - WAIT_TIME_C;
		if (time_out <= 0)
		{
			write(1, "Server Not Response\n", 20);
			exit(0);
		}
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
	if (sig == SIGUSR1)
		g_bit_index++;
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
