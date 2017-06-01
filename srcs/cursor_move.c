/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:28:14 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/30 18:43:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_begin(t_info *info)
{
	fprintf(info->fd, "Fonction go_to_begin\n");
	fprintf(info->fd, "pos_cur = %zu\n\n", info->cur_pos);
	while (info->cur_pos > 0)
		arrow_left(info);
}

void	go_to_end(t_info *info)
{
	fprintf(info->fd, "Fonction go_to_end\n");
	fprintf(info->fd, "pos_cur = %zu\n\n", info->cur_pos);
	while (info->cur_pos < info->buf_size)
		arrow_right(info);
}

void	arrow_left(t_info *info)
{
	size_t count;

	if (info->cur_pos > 0)
	{
		if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
		{
			count = info->min_line;
			ft_putstr("\033[1F");
			while (count < info->max_line)
			{
				ft_putstr("\033[1C");
				count++;
			}
			info->current_line -= 1;
		}
		else
			ft_putstr("\033[1D");
		info->cur_pos -= 1;
	}
}

void	arrow_right(t_info *info)
{
	size_t count;

	if (info->cur_pos < info->buf_size)
	{
		if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
		{
			info->current_line += 1;
			count = info->max_line;
			ft_putstr("\033[E");
			while (--count > info->min_line)
				ft_putstr("\033[1D");
		}
		else
			ft_putstr("\033[1C");
		info->cur_pos += 1;
	}
}
