/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/17 20:59:16 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	bit_index = 0;

static int	check_is_valid(int ac, char **av)
{
	if (ac != 3)
		return (0);
	if (atoi(av[1]) <= 0)
		return (0);
	return (1);
}

static void	my_sleep(size_t time)
{
	static unsigned int	oldbit;
	const int chunk = 100;
	
	while (1)
	{
		time = time + chunk;
		//printf("%d waiting\n", getpid());
		if (time > time)
		{
			//printf("%d * %d\n", bit_index, oldbit);
			time = 0;
			//write(1, "*", 1);
			break ;
		}
		if (bit_index != oldbit)
		{
			oldbit = bit_index;
			//write(1, "-", 1);
			usleep(chunk);
			break ;
		}
		usleep(chunk);
	}
}

static void	send_char(pid_t receiver, char a)
{
	unsigned char		bit;
	static unsigned int	time;
	size_t				b;
	
	//printf("send %d(%c) bit = %d\n", a, a, bit_index);
	b = bit_index % UNIT_SIZE;
	while (b < UNIT_SIZE)
	{
		bit = ((a >> (bit_index)) & 1);
		if (bit)
			kill(receiver, SIGUSR1);
		else
			kill(receiver, SIGUSR2);
		my_sleep(5000);
	}
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

static void	send_data(pid_t receiver, char *data)
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
	//printf("%d\n", bit_index);
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
	ft_printf("clientt Pid %d | server pid %d | data %s\n", getpid(), server_pid, av[1]);
	signal(SIGUSR1, h);
	signal(SIGUSR2, d);
	
	struct timeval	tv;
  	gettimeofday(&tv, NULL);
  	double begin = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
	  
	int fd = open("file.txt", O_RDONLY);
	int size = 100;
	data = malloc(size + 1);
	size = read(fd, data, size);
	//printf("%d\n", size);
	data[size + 1] = 0;
	//send_data_size(server_pid, av[1]);
	printf("%s\n", data);
	send_data(server_pid, data);

	
	gettimeofday(&tv, NULL);
	double end = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
  	printf("\nExecution time %f\n", end - begin);
	return (0);
}
