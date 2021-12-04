/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:25:58 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/20 19:03:37 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Outputs the integer ’n’ to the given
	file descriptor.
*/

static void	ft_putnbr_fd_rec(int n, int fd, int sign)
{
	if (n == 0)
		write (fd, "0", 1);
	else
	{
		if (n / 10 != 0)
			ft_putnbr_fd_rec(n / 10, fd, sign);
		ft_putchar_fd((n % 10) * sign + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		write (fd, "-", 1);
	}
	ft_putnbr_fd_rec(n, fd, sign);
}
