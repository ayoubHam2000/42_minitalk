/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:15:41 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/07 21:51:45 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	*l_get_client_p(t_lclient *lc, int pid)
{
	t_lclient *tmp;

	tmp = lc;
	while (tmp)
	{
		if (tmp->client->pid == pid)
			return (tmp->client);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*l_queue_c(t_lclient **lc, t_client c)
{
	
}