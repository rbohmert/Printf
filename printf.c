/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:30:32 by rbohmert          #+#    #+#             */
/*   Updated: 2016/10/21 20:49:20 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	init_arg(t_arg **arg, int i)
{
	if (!(*arg = (t_arg *)malloc(sizeof(t_arg))))
		exit (2);
	(*arg)->width = 0;
	(*arg)->prec = 1;
	(*arg)->place = i;
	(*arg)->arg_num = 0;
	(*arg)->arg_ptr = NULL;
	(*arg)->flag_hash = 0;
	(*arg)->flag_pad = 0;
	(*arg)->flag_add = 0;
	(*arg)->format = 0;
	(*arg)->modif = 0;
	(*arg)->result = NULL;
}

int		assemble(t_list *list, char *str, int len)
{
	t_list	*tmp;
	char	*result;
	int i = 0;
	int j = 0;

	tmp  = list;
	while (tmp)
	{
		len += ft_strlen(L(tmp)->result);
		tmp = tmp->next;
	}
	result = ft_strnew(len + 1);
	tmp = list;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			while (!isformat(str[i]))
				i++;
			ft_strcpy(&result[j], L(tmp)->format == 'x' ? ft_minu(L(tmp)->result) : L(tmp)->result);
			tmp = tmp->next;
			while (result[j])
				j++;
		}
		else 
			result[j++] = str[i];
		i++;
	}
	ft_putstr(result);
	return (ft_strlen(result));
}

void adjust(t_list *list)
{
	while (list)
	{
		if (L(list)->format > 64 && L(list)->format < 91 && L(list)->format != 'X')
		{
			L(list)->modif = 'l';
			L(list)->format += 32;
		}
		if (L(list)->format == 'p')
		{
			L(list)->arg_num = (unsigned long)L(list)->arg_ptr;
			L(list)->format = 'x';
			L(list)->flag_hash = '#';
			L(list)->flag_pad = 0;
			L(list)->flag_add = 0;
			L(list)->modif = 'l';
		}
		list = list->next;
	}
}

int		ft_printf(char *str, ...)
{
	t_list	*list;
	t_list	*tmp;
	va_list	ap;
	int lenchar;

	va_start(ap, str);
	list = NULL;
	lenchar = parsing(str, &list);
	tmp = list;
	while (tmp)
	{
		if (L(tmp)->width == -1)
			L(tmp)->width = va_arg(ap, int);
		if (L(tmp)->prec == -1)
			L(tmp)->prec = va_arg(ap, int);
		if (L(tmp)->format == 's' || L(tmp)->format == 'S' || L(tmp)->format == 'p')
			L(tmp)->arg_ptr = va_arg(ap, char *);
		else 
			L(tmp)->arg_num = va_arg(ap, long long);
		tmp = tmp->next;
	}
	adjust(list);
	format(list);
	lenchar = assemble(list, str, lenchar);
	/*while (list)
	{
		printf("wi:%d pre:%d pl:%d num:%lld fla:%c%c%c for:%c mod:%c\nresult :%s\n", L(list)->width, ((t_arg *)list->content)->prec, ((t_arg *)list->content)->place, ((t_arg *)list->content)->arg_num, ((t_arg *)list->content)->flag_hash, L(list)->flag_pad, L(list)->flag_add, ((t_arg *)list->content)->format, ((t_arg *)list->content)->modif, ((t_arg *)list->content)->result);
		list = list->next;
	}*/
	va_end(ap);
	return (lenchar);
}
