/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:47:22 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/03 22:43:09 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error(const char *error, const char *func, t_info *info)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd("abort prog\n", 2);
	info->buf != NULL ? free(info->buf) : NULL;
	exit(-1);
}

static void	init_struct(t_info *info, int fd)
{
	struct winsize w;

	ioctl(fd, TIOCGWINSZ, &w);
	info->c = 0;
	info->buf = NULL;
	info->buf_size = 0;
	info->nbr_mlc = 2;
	info->cur_pos = 0;
	info->buf_max_size = w.ws_col;
	info->begin_line = w.ws_row;
	info->current_line = 0;
	info->min_line = 3;
	info->max_line = w.ws_col;
	info->fd = fopen("log.log", "w+"); /* A supprimer */
	if (!(info->buf = (char*)malloc(sizeof(char) * (info->max_line - 3))))
		ft_error("malloc error: ", "func init_struct: ", info);
	ft_bzero(info->buf, info->max_line - 3);
}

static void	new_size(t_info *info)
{
	char	*new;
	int		count;

	new = NULL;
	count = -1;
	info->buf_max_size = info->max_line * info->nbr_mlc;
	if (!(new = malloc(sizeof(char) * info->buf_max_size)))
		ft_error("malloc error: ", "func new_size: ", info);
	ft_bzero(new, info->buf_max_size);
	while (info->buf[++count] != '\0')
		new[count] = info->buf[count];
	ft_strdel(&info->buf);
	info->buf = new;
	info->nbr_mlc += 1;
}

int			read_line(int fd, char **line)
{
	int		ret;
	t_info	info;

	init_struct(&info, fd);
	while (1)
	{
		info.cur_pos == info.buf_max_size ? new_size(&info) : 0;
		ret = read(fd, &info.c, 1);
		if (info.c == 10)
			break ;
		if (info.c == 127)
			arrow_del(&info);
		if (ft_isprint(info.c))
			add_char(&info);
		if (info.c == 27)
			which_key(fd, &info);
	}
	go_to_end(&info);
	*line = info.buf;
	fclose(info.fd);
	return (ret);
}
