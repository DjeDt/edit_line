/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:21:58 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/30 18:42:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrow_del(t_info *info)
{
	size_t count;

	if (info->buf_size > 0)
	{
		info->cur_pos -= 1;
		count = info->cur_pos;
		while (count < info->buf_size)
		{
			info->buf[count] = info->buf[count + 1];
			count++;
		}
		info->buf[count] = '\0';
		ft_putstr("\033[1D");
		ft_putstr("\033[s");
		ft_putstr("\033[J");
		ft_putstr(info->buf + info->cur_pos);
		ft_putstr("\033[u");
		info->buf_size -= 1;
	}
	if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
	{
		info->current_line -= 1;
		count = info->min_line;
		ft_putstr("\033[1A");
		while (count < info->max_line)
		{
			ft_putstr("\033[1C");
			count++;
		}
	}
}

void	arrow_rev_del(t_info *info)
{
	size_t count;

	if (info->buf_size > 0 && info->cur_pos < info->buf_size)
	{
		count = info->cur_pos;
		while ((count < info->buf_size) && info->buf[count] != '\0')
		{
			info->buf[count] = info->buf[count + 1];
			count++;
		}
		info->buf[count] = '\0';
		ft_putstr("\033[s");
		ft_putstr("\033[J");
		ft_putstr(info->buf + info->cur_pos);
		ft_putstr("\033[u");
		info->buf_size -= 1;
	}
}

void	add_char(t_info *info)
{
	size_t max;
	size_t pos;


	/*	if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
	{
//		fprintf(info->fd, "fonction add_char fonction modulo");
		info->current_line += 1;
		fprintf(info->fd, "fonction arrow_tight: current line = %zu\n", info->current_line);
		pos = info->max_line;
		ft_putstr("\033[E");
		{
			while (pos < info->min_line)
			{
				ft_putstr("\033[1D");
				pos--;
			}
		}
	}*/
	ft_putchar(info->c);
	if (info->cur_pos == info->buf_size)
	{
		info->buf[info->cur_pos++] = info->c;
		info->buf_size += 1;
	}
	else
	{
		pos = info->cur_pos;
		max = info->buf_size + 1;
		while (--max > pos)
			info->buf[max] = info->buf[max - 1];
		info->buf[max] = info->c;
		ft_putstr("\033[s");
		ft_putstr("\033[J");
		ft_putstr(info->buf + max + 1);
		ft_putstr("\033[u");
		info->cur_pos += 1;
		info->buf_size += 1;
	}
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
