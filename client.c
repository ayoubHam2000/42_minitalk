/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/22 13:05:32 by aben-ham         ###   ########.fr       */
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
		if (time > t)
		{
			time = 0;
			break ;
		}
		if (bit_index != oldbit)
		{
			oldbit = bit_index;
			usleep(chunk);
			break ;
		}
		usleep(chunk);
	}
}

static char	*get_data_size(char *data, size_t size)
{
	char	c;
	char	i;
	char	*res;

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

static void	send_bit(pid_t receiver, char *data, int index)
{
	unsigned char		bit;
	
	bit = ((data[index / UNIT_SIZE] >> (index % UNIT_SIZE)) & 1);
	if (bit)
		kill(receiver, SIGUSR1);
	else
		kill(receiver, SIGUSR2);
}

static void	send_buffer(pid_t receiver, char *data)
{
	char	hb[8];

	get_hamming_buffer(hb, data);
	bit_index = 0;
	while (bit_index < 64)
	{
		send_bit(receiver, hb, bit_index);
		my_sleep(500);
	}
	bezero(data, 7);
}

static void	send_data(pid_t receiver, char *data)
{
	char	buffer[7];
	char	*data_size;
	size_t	i;
	size_t	size;

	size = 0;
	while (data[size] != 0)
		size++;
	i = 0;
	bezero(buffer, 7);
	data_size = get_data_size(data, size);
	while (i < size + 1 + 8)
	{
		if (i < 8)
			buffer[i % 7] = data_size[i];
		else
			buffer[i % 7] = data[i - 8];
		if (i % 7 == 6)
			send_buffer(receiver, buffer);
		i++;
		//printf("\n");
	}
	if (i % 7 != 0)
		send_buffer(receiver, buffer);
}

void next_bit(int sig)
{
	bit_index++;
}

void error_handler(int sig)
{
	printf("%lu resend from %d\n", get_time(), getpid());
	bit_index = 0;
}

char	*git_data_from_file()
{
	char	*data;

	int fd = open("file.txt", O_RDONLY);
	int size = 10000;
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
	printf("clientt Pid %d | server pid %d | data %s\n", getpid(), server_pid, git_data_from_file());
	signal(SIGUSR1, next_bit);
	signal(SIGUSR2, error_handler);
	
	struct timeval	tv;
  	gettimeofday(&tv, NULL);
  	double begin = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
	  
	
	//printf("%s\n", av[1]);
	//send_data(server_pid, av[1]);
	send_data(server_pid, git_data_from_file());
	
	gettimeofday(&tv, NULL);
	double end = (tv.tv_sec) * 1000000 + (tv.tv_usec) ;
  	printf("\nExecution time %f\n", end - begin);
	return (0);
}
