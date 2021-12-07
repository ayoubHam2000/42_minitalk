/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/07 21:08:21 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_is_valid(int ac, char **av)
{
	if (ac != 3)
		return (0);
	if (atoi(av[1]) <= 0)
		return (0);
	return (1);
}

static void	send_unit(pid_t receiver, unsigned int a)
{
	unsigned int	i;
	unsigned int	bit;

	i = 0;
	while (i < UNIT_SIZE)
	{
		usleep(WAIT_TIME);
		bit = (a & 1);
		if (bit)
			kill(receiver, SIGUSR1);
		else
			kill(receiver, SIGUSR2);
		a = (a >> 1);
		i++;
		pause();
	}
}

static int	send_chunk(pid_t receiver, char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && i < CHUNK_SIZE + start)
	{
		send_unit(receiver, str[i]);
		i++;
	}
	if (!str[i])
		return (1);
	return (0);
}

void h(int sig)
{
	//write(1, "*", 1);
	return ;
}

int main(int ac, char **av)
{
	pid_t	server_pid;
	char	*data;

	server_pid = get_server_pid();
	data = av[1];
	ft_printf("client Pid %d | server pid %d\n", getpid(), server_pid);
	signal(SIGUSR1, h);
	
	
	struct timeval	tv;
  	gettimeofday(&tv, NULL);
  	double begin = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
	  
	
	int i = 0;
	while (i++ < 2000)
		send_unit(server_pid, i*2);

	
	gettimeofday(&tv, NULL);
	double end = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
  	printf("\nExecution time %f\n", end - begin);
	return (0);
}
