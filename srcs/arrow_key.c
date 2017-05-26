/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:21:58 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/25 20:56:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (info->cur_pos < ft_strlen(info->buf))
		ft_putstr("\033[1C");
	info->cur_pos++;
}

void	arrow_delete(t_info *info)
{
	ft_putendl("delete");
	(void)info;
}

void	add_char(t_info *info)
{
	char	save;
	size_t	count;

	ft_putchar(info->c);
	fprintf(info->fd, "\n\nFonction add_char:\n");
	count = info->cur_pos;
	fprintf(info->fd, "curseur = %zu | char = %c\n", count, info->c);
	if (info->cur_pos == ft_strlen(info->buf))
	{
		fprintf(info->fd, "if\n");
		info->buf[info->cur_pos] = info->c;
	}
	else
	{
		fprintf(info->fd, "else\n");
		fprintf(info->fd, "avant modif buf = %s\n", info->buf);
		while (info->buf[count])
		{
			fprintf(info->fd, "new buf = %s\n", info->buf);
			save = info->buf[count];
			info->buf[count] = info->c;
			count++;
			info->c = info->buf[count];
			info->buf[count] = save;
			ft_putchar(info->buf[count]);
			save = info->c;
			count++;
		}
//		ft_putstr("\033[K");
		fprintf(info->fd, "apres modif buf = %s\n", info->buf);
//		ft_putstr(info->buf + info->cur_pos);
	}
	info->cur_pos++;
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
		else if (info->c == '3')
			arrow_delete(info);
	}
}
