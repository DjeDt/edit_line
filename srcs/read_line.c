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
/*
static void	special_input(const char *str, int save, int count)
{
	if ()
}
*/

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
	char tmp[2];

	read(fd, &tmp, 2);
	if (tmp[0] == '[' && tmp[1] == 'C')
		arrow_left();
	else if (tmp[0] == '[' && tmp[1] == 'D')
		arrow_right();
	else if (tmp[0] == '[' && tmp[1] == '3')
		arrow_delete();
}

int		read_line(int fd, char **line)
{
	char	*buf;
	int		count;
	int		ret;

	if (!(buf = (char*)malloc(sizeof(char) * 256)))
	{
		ft_putendl_fd("error malloc readline: abort", 2);
		exit (-1);
	}
	count = 0;
	while (1)
	{
		ret = read(fd, buf + count, 1);
		if (buf[count] == 10)
			break ;
		if (buf[count] == 27)
			which_key(fd);
		count++;
	}
	buf[count] = '\0';
	*line = buf;
	return (ret);
}
