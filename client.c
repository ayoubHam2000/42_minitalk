/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/17 23:10:38 by aben-ham         ###   ########.fr       */
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

static void	my_sleep(size_t t)
{
	static unsigned int	oldbit;
	static size_t	time;
	const int chunk = 100;
	
	while (1)
	{
		time = time + chunk;
		//printf("%d waiting\n", getpid());
		if (time > t)
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

static void	send_bit(pid_t receiver, char *data, int index)
{
	unsigned char		bit;
	
	bit = ((data[index / UNIT_SIZE] >> (index % UNIT_SIZE)) & 1);
	if (bit)
		kill(receiver, SIGUSR1);
	else
		kill(receiver, SIGUSR2);
	printf("send %d\n", bit);
}

static char	*get_data_size(pid_t receiver, char *data)
{
	size_t	size;
	char	c;
	char	i;
	char	*res;

	size = 0;
	while (*data++ != 0)
		size++;
	res = malloc(8);
	if (!res)
	{
		printf("No Space In Memory");
		exit(1);
	}
	i = 0;
	while (i < 8)
	{
		c = *((char *)(&size));
		res[i] = c;
		size = size >> 8;
		i++;
	}
	return (res);
}

static void	send_data(pid_t receiver, char *data)
{
	char	*data_size;
	size_t	size;

	size = 0;
	while (data[size] != 0)
		size++;
	if (size == 0)
		return ;
	data_size = get_data_size(receiver, data);
	size = size * UNIT_SIZE + 64;
	while (bit_index < size + 8)
	{
		if (bit_index < 64)
			send_bit(receiver, data_size, bit_index);
		else
			send_bit(receiver, data, bit_index - 64);
		my_sleep(500000);
	}	
}

void h(int sig)
{
	bit_index++;
}

void d(int sig)
{
	if (bit_index > 57)
		bit_index = bit_index - 57;
}

char	*git_data_from_file()
{
	char	*data;

	int fd = open("file.txt", O_RDONLY);
	int size = 100;
	data = malloc(size + 1);
	size = read(fd, data, size);
	//printf("%d\n", size);
	data[size + 1] = 0;
	return (data);
}

int main(int ac, char **av)
{
	pid_t	server_pid;

	server_pid = get_server_pid();
	ft_printf("clientt Pid %d | server pid %d | data %s\n", getpid(), server_pid, av[1]);
	signal(SIGUSR1, h);
	signal(SIGUSR2, d);
	
	struct timeval	tv;
  	gettimeofday(&tv, NULL);
  	double begin = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
	  
	
	printf("%s\n", av[1]);
	send_data(server_pid, av[1]);

	
	gettimeofday(&tv, NULL);
	double end = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
  	printf("\nExecution time %f\n", end - begin);
	return (0);
}
