/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:50:11 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/22 13:28:31 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int get_server_pid()
{
	int pid;

	FILE *f = fopen("pid.txt", "r");
	fscanf(f, "%d", &pid);
	fclose(f);
	return (pid);
}

void share_server_pid()
{
	FILE *f = fopen("pid.txt", "w");
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
