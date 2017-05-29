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
	while (info->cur_pos > 0)
		arrow_left(info);
}

void	go_to_end(t_info *info)
{
	while (info->cur_pos < info->buf_size)
		arrow_right(info);
}

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
	if (info->cur_pos < info->buf_size)
	{
		info->cur_pos++;
		ft_putstr("\033[1C");
	}
}
