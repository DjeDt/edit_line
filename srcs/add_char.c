/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:43:30 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/10 15:12:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	check_cur_pos(t_info *info)
{
	if (((info->cur_pos + 3) % info->max_line) == 0)
	{
		ft_putstr("\033[1E");
		info->current_line += 1;
	}
}

static void	reprint_line(const char *str)
{
	ft_putstr("\033[s");
	ft_putstr("\033[0J");
	ft_putstr(str);
	ft_putstr("\033[u");
}

void		add_char(t_info *info)
{
	int max;
	int pos;

	ft_putchar(info->c);
	if (info->cur_pos == info->buf_size)
		info->buf[info->cur_pos] = info->c;
	else
	{
		pos = info->cur_pos;
		max = info->buf_size;
		while (max > pos)
		{
			info->buf[max] = info->buf[max - 1];
			max--;
		}
		info->buf[info->cur_pos] = info->c;
	}
	save_current_buf(info);
	info->buf_size += 1;
	info->cur_pos += 1;
	check_cur_pos(info);
	reprint_line(info->buf + info->cur_pos);
}
