/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:28:14 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/08 18:38:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

#include <stdio.h>

void	go_to_begin(t_info *info)
{
	int ret;

	ret = 0;
	while (ret == 0)
		ret = arrow_left(info);
}

void	go_to_end(t_info *info)
{
	int	ret;

	ret = 0;
	while (ret == 0)
		ret = arrow_right(info);
}

int		arrow_left(t_info *info)
{
	if (info->cur_pos > 0)
	{
		if (((info->cur_pos + 3) % info->max_line) == 0)
		{
			ft_putstr("\033[1F");
			ft_putstr("\033[1000C");
			info->current_line -= 1;
		}
		else
			ft_putstr("\033[1D");
		info->cur_pos -= 1;
		return (0);
	}
	else
		return (-1);
}

int		arrow_right(t_info *info)
{
	if (info->cur_pos < info->buf_size)
	{
		info->cur_pos += 1;
		if (((info->cur_pos + 3) % info->max_line) == 0)
		{
			ft_putstr("\033[1E");
			info->current_line += 1;
		}
		else
			ft_putstr("\033[1C");
		return (0);
	}
	else
		return (-1);
}
