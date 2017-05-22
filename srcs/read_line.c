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

int		read_line(int fd, char **line)
{
	char	*buf;
	int		count;
	int		ret;
	int		save;

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
		if (buf[count] == '[')
			save = count;
		if (buf[save] == '[' && buf[save + 1] == 'A')
			ft_putendl("up");
		if (buf[save] == '[' && buf[save + 1] == 'B')
			ft_putendl("down");
		if (buf[save] == '[' && buf[save + 1] == 'C')
			ft_putendl("right");
		if (buf[save] == '[' && buf[save + 1] == 'D')
			ft_putendl("left");
		if (buf[save] == '[' && buf[save + 1] == '3')
			ft_putendl("delete");
		count++;
	}
	buf[count] = '\0';
	*line = buf;
	return (ret);
}
