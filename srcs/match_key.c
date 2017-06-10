/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:06:36 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/07 15:36:07 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	which_key_2(int fd, t_info *info)
{
	read(fd, &info->c, 1);
	if (info->c == '[')
	{
		read(fd, &info->c, 1);
		if (info->c == 'C')
			arrow_right(info);
		else if (info->c == 'D')
			arrow_left(info);
		else if (info->c == 'A')
			history_up(info, &info->hist);
		else if (info->c == 'B')
			history_down(info, &info->hist);
		else if (info->c == 'H')
			go_to_begin(info);
		else if (info->c == 'F')
			go_to_end(info);
		else if (info->c == '3')
		{
			read(fd, &info->c, 1);
			if (info->c == '~')
				key_delete_rev(info);
		}
	}
}

int			which_key(int fd, t_info *info)
{
	if (info->c == 10)
		return (-1);
	else if (info->c == 127)
		key_delete(info);
	else if (info->c == 27)
		which_key_2(fd, info);
	return (0);
}
