/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:21:58 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/26 18:13:54 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrow_left(t_info *info)
{
	if (info->cur_pos > 0)
	{
		info->cur_pos--;
		ft_putstr("\033[1D");
	}
}

void	arrow_right(t_info *info)
{
	if (info->cur_pos == info->char_max)
	{
		/* GERER LE NBR DE LIGNE */
	}
	if (info->cur_pos < ft_strlen(info->buf))
		ft_putstr("\033[1C");
	info->cur_pos++;
}

void	arrow_del(t_info *info)
{

	size_t count;
	size_t max;

	if (ft_strlen(info->buf) < 1)
		return ;
	count = info->cur_pos - 1;
	max = ft_strlen(info->buf);
	while (count < max)
	{
		info->buf[count] = info->buf[count + 1];
		count++;
	}
	info->buf[count] = '\0';
	ft_putstr("\033[1D");
	ft_putstr("\033[0K");
	ft_putstr("\033[s");
	ft_putstr(info->buf + info->cur_pos - 1);
	ft_putstr("\033[u");
	info->cur_pos--;
}

void	arrow_rev_del(t_info *info)
{
	ft_putendl("delete");
	(void)info;
}

static void decal_char(char *str, const char c, const size_t pos)
{
	size_t count;
	size_t max;

	count = pos + 1;
	max = ft_strlen(str);
	while (max > pos)
	{
		str[max] = str[max - 1];
		max--;
	}
	str[max] = c;
	ft_putstr("\033[0K");
	ft_putstr("\033[s");
	ft_putstr(str + max + 1);
	ft_putstr("\033[u");
}

void	add_char(t_info *info)
{
	ft_putchar(info->c);
	if (info->cur_pos == ft_strlen(info->buf))
		info->buf[info->cur_pos] = info->c;
	else
		decal_char(info->buf, info->c, info->cur_pos);
	info->cur_pos++;
}

void	which_key(int fd, t_info *info)
{
	read(fd, &info->c, 1);
	if (info->c == '[')
	{
		read(fd, &info->c, 1);
		if (info->c == 'C')
			arrow_right(info);
		else if (info->c == 'D')
			arrow_left(info);
		else if (info->c == '3')
			arrow_rev_del(info);
	}
}
