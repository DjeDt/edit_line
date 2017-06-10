/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:44:33 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/10 16:16:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

#include <stdio.h>

void		save_current_buf(t_info *info)
{
	info->save_buf != NULL ? ft_strdel(&info->save_buf) : NULL;
	info->save_buf = ft_strdup(info->buf);
}

void		maj_hist(t_info *info)
{
	if (info->buf[0] != '\0')
		ft_putendl_fd(info->buf, info->hist_fd);
	if (info->hist != NULL)
		free_hist(&info->hist);
	if (info->save_buf != NULL)
		ft_strdel(&info->save_buf);
	close(info->hist_fd);
}

static void	put_in_buf(const char *str, t_info *info)
{
	go_to_begin(info);
	ft_putstr("\033[J");
	ft_bzero(info->buf, info->buf_max_size);
	info->buf_size = 0;
	while (str && str[info->cur_pos] != '\0')
	{
		info->buf[info->cur_pos] = str[info->cur_pos];
		info->cur_pos += 1;
		info->buf_size += 1;
	}
	ft_putstr(str);
}

int			history_up(t_info *info, t_hist **hist)
{
	t_hist	*tmp;

	if (*hist == NULL)
		return (-1);
	tmp = *hist;
	if (info->cur_hist > 0)
		info->cur_hist -= 1;
	while (tmp->next != NULL)
	{
		if (info->cur_hist == tmp->cur)
			break ;
		tmp = tmp->next;
	}
	put_in_buf(tmp->value, info);
	return (0);
}

int			history_down(t_info *info, t_hist **hist)
{
	t_hist	*tmp;

	if (*hist == NULL)
		return (-1);
	tmp = *hist;
	info->cur_hist += 1;
	if (info->cur_hist >= info->max_hist)
	{
		put_in_buf(info->save_buf, info);
		info->cur_hist = info->max_hist;
	}
	else
	{
		while (tmp->next != NULL)
		{
			if (info->cur_hist == tmp->cur)
				break ;
			tmp = tmp->next;
		}
		put_in_buf(tmp->value, info);
	}
	return (0);
}
