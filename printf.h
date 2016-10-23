/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:30:49 by rbohmert          #+#    #+#             */
/*   Updated: 2016/03/27 00:51:41 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# define L(a) ((t_arg *)(a->content))

#include "libft/libft.h"
#include <stdio.h>
#include <stdarg.h>

typedef struct	s_arg
{
	int			width;
	int			prec;
	int			place;
	long long	arg_num;
	void		*arg_ptr;
	char		*result;
	char		flag_hash;
	char		flag_pad;
	char		flag_add;
	char		format;
	char		modif;
}				t_arg;

int		isformat(char c);
void	init_arg(t_arg **arg, int i);
int		get_arg(t_list **list, int i, char *str);
int		parsing(char *str, t_list **list);
int		ft_printf(char *str, ...);
void	format(t_list *list);
void	app_flag(t_arg *arg);
void	app_mod(t_arg *arg);
void	app_prefix(t_arg *arg);
void	app_width(t_arg *arg);
void	app_prec(t_arg *arg);
#endif
