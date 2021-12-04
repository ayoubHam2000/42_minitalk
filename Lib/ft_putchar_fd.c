/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:09:58 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/20 19:07:57 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Écrit le caractère ’c’ sur le file descriptordonné
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
