/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:48:40 by rbohmert          #+#    #+#             */
/*   Updated: 2016/10/21 20:48:03 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	app_prec(t_arg *arg)
{
	char	*res;
	int 	i;

	i = 0;
	if (arg->format == 's' && arg->prec != 1 && (int)ft_strlen(arg->result) > arg->prec)
		arg->result[arg->prec] = 0;
	if ((arg->format == 'd' || arg->format == 'i' || arg->format == 'o' || arg->format == 'u' || arg->format == 'x') && (int)ft_strlen(arg->result) < arg->prec )
	{	
		if (!(res = (char *)malloc(arg->prec + 1)))
			return ;
		while (i < (int)(arg->prec - ft_strlen(arg->result)))
			res[i++] = '0';
		ft_strcat(res, arg->result);
		free(arg->result);
		arg->result = res;
	}
	if (arg->prec == 0)
	{
		arg->result[0] = 0;
		arg->flag_add = 0;
		arg->flag_hash = 0;
		arg->width = 0;
	}
}

void	add_width(t_arg *arg)
{
	char	*res;
	int		i;

	getchar();
	i = 0;
	res = ft_strnew(arg->width + 1);
	if (arg->flag_pad == '-')
	{
		ft_strcpy(res, arg->result);
		i = ft_strlen(arg->result);
		while (i < arg->width)
			res[i++] = ' ';
	}
	else
	{
		while (i < (int)(arg->width - ft_strlen(arg->result)))
			res[i++] = (arg->flag_pad == '0' && arg->prec != 1) ? '0' : ' ';
		ft_strcat(res, arg->result);
	}
	free(arg->result);
	arg->result = res;
}			

void	add_prefix(t_arg *arg)
{
	char *res;

	if (!(res = (char *)malloc(ft_strlen(arg->result) + 3)))
		return ;
	if ((arg->format == 'x' || arg->format == 'X' || arg->format == 'o') && arg->flag_hash)
	{
		(arg->format == 'o') ? ft_strcpy(res, "0") : ft_strcpy(res, "0X");
		ft_strcat(res, arg->result);
		free(arg->result);
		arg->result = res;
	}
	if ((arg->format == 'd' || arg->format == 'i') && (arg->flag_add && arg->arg_num > 0))
	{
		res[0] = arg->flag_add;	
		ft_strcat(res, arg->result);
		free(arg->result);
		arg->result = res;
	}
}

void	app_mod(t_arg *arg)
{
	if (arg->format == 'd' || arg->format == 'i')
	{
		arg->arg_num = (arg->modif == 'H') ? (char)arg->arg_num : arg->arg_num;
		arg->arg_num = (arg->modif == 'h') ? (short)arg->arg_num : arg->arg_num;
		arg->arg_num = (arg->modif == 'l') ? (long)arg->arg_num : arg->arg_num;
		arg->arg_num = (!arg->modif) ? (int)arg->arg_num : arg->arg_num;
	}
	if (arg->format == 'u' || arg->format == 'o' || arg->format == 'X' || arg->format == 'x')
	{	
		arg->arg_num = (arg->modif == 'H') ? (unsigned char)arg->arg_num : arg->arg_num;
		arg->arg_num = (arg->modif == 'h') ? (unsigned short)arg->arg_num : arg->arg_num;
		arg->arg_num = (arg->modif == 'l') ? (unsigned long)arg->arg_num : arg->arg_num;
		arg->arg_num = (!arg->modif) ? (unsigned int)arg->arg_num : arg->arg_num;
	}
}

void	format(t_list *list)
{
	while (list)
	{
		app_mod(L(list));
		if (L(list)->format == '%')
			L(list)->result = ft_strdup("%");
		if (L(list)->format == 'u' || L(list)->format == 'd' || L(list)->format == 'i')
			L(list)->result =  ft_itoa_base(L(list)->arg_num, 10);
		if (L(list)->format == 'X' || L(list)->format == 'x')
			L(list)->result =  ft_itoa_base(L(list)->arg_num, 16);
		if (L(list)->format == 'o')
			L(list)->result = ft_itoa_base(L(list)->arg_num, 8);
		if (L(list)->format == 's')
			L(list)->result = ft_strdup(L(list)->arg_ptr);
		if (L(list)->format == 'c')
			return ;
		app_prec(L(list));
		if (L(list)->flag_hash || L(list)->flag_add)
			add_prefix(L(list));
		if (L(list)->width > (int)ft_strlen(L(list)->result))
			add_width(L(list));
		list = list->next;
	}
}
