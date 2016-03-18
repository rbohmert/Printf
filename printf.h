/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:30:49 by rbohmert          #+#    #+#             */
/*   Updated: 2016/03/18 22:30:51 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdarg.h>

typedef struct	s_arg
{
	int			width;
	int			prec;
	int			place;
	int			arg_num;
	char		*arg_str;
	char		*result;
	char		flag;
	char		format;
	char		modif;
}				t_arg;

int		isformat(char c);
void	init_arg(t_arg **arg, int i);
int		get_arg(t_list **list, int i, char *str);
void	parsing(char *str, t_list **list);
int		ft_printf(char *str, ...);
#endif
