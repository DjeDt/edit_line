/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:21:58 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/29 20:47:13 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrow_del(t_info *info)
{
	size_t count;

	if (info->buf_size > 0)
	{
		count = info->cur_pos - 1;
		while (count < info->buf_size)
		{
			info->buf[count] = info->buf[count + 1];
			count++;
		}
		info->buf[count] = '\0';
		ft_putstr("\033[1D");
		ft_putstr("\033[s");
		ft_putstr("\033[J");
		ft_putstr(info->buf + (--info->cur_pos));
		ft_putstr("\033[u");
	}
}

void	arrow_rev_del(t_info *info)
{
	size_t max;
	size_t count;

//	if (info->buf[info->cur_pos + 1] && info->buf[info->cur_pos + 1] == '\0')
//		return ;
	if (info->buf_size > 0 && info->cur_pos < info->buf_size)
	{

		count = info->cur_pos;
		max = ft_strlen(info->buf) + 1;
		while (count < max && info->buf[count] != '\0')
		{
			info->buf[count] = info->buf[count + 1];
			count++;
		}
		info->buf[count] = '\0';
		ft_putstr("\033[s");
		ft_putstr("\033[J");
		ft_putstr(info->buf + info->cur_pos);
		ft_putstr("\033[u");
	}
}

void	add_char(t_info *info)
{
	size_t max;
	size_t pos;

	ft_putchar(info->c);
	if (info->cur_pos == ft_strlen(info->buf))
		info->buf[info->cur_pos] = info->c;
	else
	{
		max = ft_strlen(info->buf);
		pos = info->cur_pos;
		while (max > pos)
		{
			info->buf[max] = info->buf[max - 1];
			max--;
		}
		info->buf[max] = info->c;
		ft_putstr("\033[s");
		ft_putstr("\033[J");
		ft_putstr(info->buf + max + 1);
		ft_putstr("\033[u");
	}
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
		else if (info->c == 'H')
			go_to_begin(info);
		else if (info->c == 'F')
			go_to_end(info);
		else if (info->c == '3')
		{
			read(fd, &info->c, 1);
			if (info->c == '~')
				arrow_rev_del(info);
		}
	}
}
