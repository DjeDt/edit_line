/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:47:22 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/18 12:25:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrow_left()
{
	ft_putstr("\033[1C");
}

void	arrow_right()
{
	ft_putstr("\033[1D");
}

void	arrow_delete()
{
	ft_putendl("delete");
}

void	which_key(int fd)
{
	char c;

	read(fd, &c, 1);
	if (c == '[')
	{
		read(fd, &c, 1);
		if (c == 'C')
			arrow_left();
		else if (c == 'D')
			arrow_right();
		else if (c == '3')
			arrow_delete();
	}
}

int		read_line(int fd, char **line)
{
	int		count;
	int		ret;
	t_info	info;

	if (!(info.buf = (char*)malloc(sizeof(char) * 256)))
	{
		ft_putendl_fd("error malloc readline: abort", 2);
		exit (-1);
	}
	count = 0;
	while (1)
	{
		ret = read(fd, info.buf + count, 1);
		if (info.buf[count] == 10)
			break ;
		if (info.buf[count] == 27)
			which_key(fd);
		if (ft_isprint(info.buf[count]))
			ft_putchar(info.buf[count]);
		count++;
	}
	info.buf[count] = '\0';
	*line = info.buf;
	return (ret);
}
