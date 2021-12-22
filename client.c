/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/22 15:39:31 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_bit_index = 0;

static int	check_is_valid(int ac, char **av)
{
	if (ac != 3)
		return (0);
	if (atoi(av[1]) <= 0)
		return (0);
	return (1);
}

static void	send_char(pid_t receiver, char c)
{
	unsigned int	bit;

	while (g_bit_index < 8)
	{
		bit = ((c >> g_bit_index) & 1);
		if (bit)
			kill(receiver, SIGUSR1);
		else
			kill(receiver, SIGUSR2);
		usleep(50);
	}
	g_bit_index = 0;
}

static void	send_data(pid_t receiver, char *data)
{
	size_t	size;
	int		i;
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
		printf("%d\n", i - 8);
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

int main(int ac, char **av)
{
	pid_t	server_pid;

	server_pid = get_server_pid();
	printf("clientt Pid %d | server pid %d | data %s\n", getpid(), server_pid, av[1]);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	
	struct timeval	tv;
  	gettimeofday(&tv, NULL);
  	double begin = (tv.tv_sec) * 1000000 + (tv.tv_usec);
	  
	
	send_data(server_pid, git_data_from_file());
	
	gettimeofday(&tv, NULL);
	double end = (tv.tv_sec) * 1000000 + (tv.tv_usec);
  	printf("\nExecution time %f\n", end - begin);
	return (0);
}
