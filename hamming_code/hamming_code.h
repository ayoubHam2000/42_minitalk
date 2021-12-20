/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamming_code.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:04:28 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/20 14:21:44 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAMMING_CODE_H
# define HAMMING_CODE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# define HM_OR 8

//hamming_util
char	parity_l(char c);
char	parity_v(char *bits);
char	parity_h(char *bits);
char	parity_bc(char *bits, int nb);
char	parity_all(char *bits);

//hamming_buffer
void	add_to_buffer(char *buffer, char bit);
void	add_parity_check(char *buffer);
void	get_hamming_buffer(char *buffer, char *message);
void	extract_from_hamming(char *message, char *buffer);

// hamming_code
char	hammingc(char *bits);

#endif