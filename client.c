/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/11 00:44:06 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int	bit_index = 0;

static int	check_is_valid(int ac, char **av)
{
	if (ac != 3)
		return (0);
	if (atoi(av[1]) <= 0)
		return (0);
	return (1);
}

static void	send_char(pid_t receiver, char a)
{
	unsigned char	bit;

	//printf("send %d(%c)\n", a, a);
	while (bit_index < UNIT_SIZE)
	{
		bit = ((a >> (bit_index)) & 1);
		if (bit)
			kill(receiver, SIGUSR1);
		else
			kill(receiver, SIGUSR2);
		//ft_printf("From %d Send To Sever bit = (%d, %d)\n",getpid(), bit_index+1, bit);
		//pause();
		usleep(5000);
	}
	bit_index = 0;
	//write(1, "end\n", 4);
}

static void send_data_size(pid_t receiver, char *data)
{
	size_t	size;
	char	c;
	char	i;

	size = 0;
	while (*data++ != 0)
		size++;
	while (i < 8)
	{
		c = *((char *)(&size));
		send_char(receiver, c);
		size = size >> 8;
		i++;
	}
}

static int	send_data(pid_t receiver, char *data)
{
	send_data_size(receiver, data);
	while (*data)
	{
		send_char(receiver, *data);
		data++;
	}
	send_char(receiver, 0);
}

void h(int sig)
{
	//ft_printf("%d => %d\n", getpid(), bit_index);
	bit_index++;
}

void d(int sig)
{
	write(1, "Server Error\n", 14);
	exit(0);
}

int main(int ac, char **av)
{
	pid_t	server_pid;
	char	*data;

	server_pid = get_server_pid();
	data = av[1];
	ft_printf("client Pid %d | server pid %d | data %u\n", getpid(), server_pid, atoi(av[1]));
	signal(SIGUSR1, h);
	signal(SIGUSR2, d);
	
	struct timeval	tv;
  	gettimeofday(&tv, NULL);
  	double begin = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
	  
	int fd = open("file.txt", O_RDONLY);
	int size = 1000;
	data = malloc(size + 1);
	size = read(fd, data, size);
	printf("%d\n", size);
	data[size + 1] = 0;
	//send_data_size(server_pid, av[1]);
	printf("%s\n", data);
	send_data(server_pid, data);

	
	gettimeofday(&tv, NULL);
	double end = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
  	printf("\nExecution time %f\n", end - begin);
	return (0);
}
