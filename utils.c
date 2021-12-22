/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:50:11 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/22 15:40:36 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int get_server_pid()
{
	int	pid;

	FILE *f = fopen("ppid", "r");
	fscanf(f, "%d", &pid);
	fclose(f);
	return (pid);
}

void share_server_pid()
{
	FILE *f = fopen("ppid", "w");
	fprintf(f, "%d", getpid());
	fclose(f);
}

unsigned  long time_micro()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000000 + tp.tv_usec;
	return (ms);
}

char	*git_data_from_file()
{
	char	*data;

	int fd = open("file.txt", O_RDONLY);
	int size = 1000;
	data = malloc(size + 1);
	size = read(fd, data, size);
	//printf("%d\n", size);
	data[size + 1] = 0;
	return (data);
}

void	print_bits(char c)
{
	short	i;
	char	b;

	i = 0;
	while (i < 8)
	{
		b = ((c >> (8 - i - 1)) & 1) + '0';
		write(1, &b, 1);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
