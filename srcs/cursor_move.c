/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:28:14 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/29 21:50:12 by ddinaut          ###   ########.fr       */
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
	fprintf(info->fd, "Fonction arrow_left\n");
	fprintf(info->fd, "pos_cur = %zu\n\n", info->cur_pos);
	if (info->cur_pos > 0)
	{
		info->cur_pos--;
		ft_putstr("\033[1D");
	}
}

void	arrow_right(t_info *info)
{
	fprintf(info->fd, "Fonction arrow_right\n");
	fprintf(info->fd, "pos_cur = %zu\n", info->cur_pos);
	if (((info->cur_pos + 3) % info->char_max_by_line) == 0)
	{
		fprintf(info->fd, "option modulo\n\n");
		info->cur_pos++;
		ft_putstr("\033[1E");
	}
	else if (info->cur_pos < info->buf_size)
	{
		fprintf(info->fd, "option normale\n\n");
		info->cur_pos++;
		ft_putstr("\033[1C");
	}
}
