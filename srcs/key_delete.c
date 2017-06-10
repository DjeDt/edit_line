/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 14:34:00 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/04 20:24:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	check_cur_pos(t_info *info)
{
	if (((info->cur_pos + 3) % info->max_line) == 0)
	{
		ft_putstr("\033[1F");
		ft_putstr("\033[1000C");
		info->current_line -= 1;
	}
	else
		ft_putstr("\033[1D");
}

static void	reprint_line(const char *str)
{
	ft_putstr("\033[s");
	ft_putstr("\033[0J");
	ft_putstr(str);
	ft_putstr("\033[u");
}

void		key_delete(t_info *info)
{
	int count;

	if (info->buf_size > 0)
	{
		check_cur_pos(info);
		count = info->cur_pos - 1;
		while (count <= info->buf_size)
		{
			info->buf[count] = info->buf[count + 1];
			count++;
		}
		info->cur_pos -= 1;
		reprint_line(info->buf + info->cur_pos);
		info->buf_size -= 1;
	}
}

void		key_delete_rev(t_info *info)
{
	int count;

	if (info->buf_size > 0 && info->cur_pos < info->buf_size)
	{
		count = info->cur_pos;
		while ((count < info->buf_size) && (info->buf[count] != '\0'))
		{
			info->buf[count] = info->buf[count + 1];
			count++;
		}
		info->buf[count] = '\0';
		reprint_line(info->buf + info->cur_pos);
		info->buf_size -= 1;
	}
}
