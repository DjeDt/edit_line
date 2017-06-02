/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:28:14 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/02 22:39:35 by ddinaut          ###   ########.fr       */
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
	if (info->cur_pos > 0)
	{
		fprintf(info->fd, "arrow_left: curseur = %zu, lettre = %c\n", info->cur_pos, info->buf[info->cur_pos]);
		info->cur_pos -= 1;
		if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
		{
			ft_putstr("\033[1F");
			ft_putstr("\033[1000C");
			info->current_line -= 1;
		}
		else
			ft_putstr("\033[1D");
	}
}

void	arrow_right(t_info *info)
{
	if (info->cur_pos < info->buf_size)
	{
		if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
		{
			ft_putstr("\033[E");
			info->current_line += 1;
		}
		else
			ft_putstr("\033[1C");
		info->cur_pos += 1;
	}
}
