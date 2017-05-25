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

void	arrow_left(t_info info)
{
	if (info.cur_pos > 0)
		ft_putstr("\033[1D");
}

void	arrow_right(t_info info)
{
	if (info.cur_pos < ft_strlen(info.buf))
		ft_putstr("\033[1C");
}

void	arrow_delete(t_info info)
{
	ft_putendl("delete");
	(void)info;
}

void	which_key(int fd, t_info info)
{
	char c;

	read(fd, &c, 1);
	if (c == '[')
	{
		read(fd, &c, 1);
		if (c == 'C')
			arrow_right(info);
		else if (c == 'D')
			arrow_left(info);
		else if (c == '3')
			arrow_delete(info);
	}
}

static void init_struct(t_info *info, int fd)
{
	struct winsize w;

	ioctl(fd, TIOCGWINSZ, &w);

	info->char_max = w.ws_col;
	info->len_max = w.ws_col;
	info->nb_line = w.ws_row;
	if (!(info->buf = (char*)malloc(sizeof(char) * info->char_max - 2))) // - 2 == + 1 - 3 -> (- 3 pour la taille du prompt)
	{
		ft_putendl("error malloc init struct");
		exit (-1);
	}
}

static void	new_size(t_info *info)
{
	char		*new;
	size_t		count;
	static int	nbr = 2;

	new = NULL;
	info->len_max = info->char_max * nbr;
	if (!(new = malloc(sizeof(char) * info->len_max + 1)))
	{
		ft_putendl("error malloc new_size");
		exit (-1);
	}
	count = -1;
	while (info->buf[++count])
		new[count] = info->buf[count];
	new[++count] = '\0';
	free(info->buf);
	info->buf = new;
	nbr += 1;
}

int		read_line(int fd, char **line)
{
	int		ret;
	t_info	info;

	init_struct(&info, fd);
	info.cur_pos = 0;
	while (1)
	{
		if (info.cur_pos == (size_t)info.len_max)
			new_size(&info);
		ret = read(fd, info.buf + info.cur_pos, 1);
		if (info.buf[info.cur_pos] == 10 || ret > 1)
			break ;
		if (info.buf[info.cur_pos] == 27)
			which_key(fd, info);
		if (ft_isprint(info.buf[info.cur_pos]))
			ft_putchar(info.buf[info.cur_pos]);
		info.cur_pos++;
	}
	info.buf[info.cur_pos] = '\0';
	*line = info.buf;
	return (ret);
}
