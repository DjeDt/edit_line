/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:47:22 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/10 16:00:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	ft_error(const char *error, const char *func, t_info *info)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd("abort prog\n", 2);
	info->buf != NULL ? free(info->buf) : NULL;
	info->save_buf != NULL ? free(info->save_buf) : NULL;
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
	info->max_nbr_line = w.ws_row;
	info->current_line = 0;
	info->max_line = w.ws_col;
	info->cur_hist = 0;
	info->max_hist = 0;
	info->hist = NULL;
	info->save_buf = NULL;
	info->hist_fd = open(".history", O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (!(info->buf = (char*)malloc(sizeof(char) * (info->max_line - 3))))
		ft_error("malloc error: ", "func init_struct: ", info);
	ft_bzero(info->buf, info->max_line - 3);
}

static void	new_size(t_info *info)
{
	char	*new;

	new = NULL;
	info->buf_max_size = info->max_line * info->nbr_mlc;
	if (!(new = malloc(sizeof(char) * info->buf_max_size)))
		ft_error("malloc error: ", "func new_size: ", info);
	ft_bzero(new, info->buf_max_size);
	ft_memcpy(new, info->buf, info->buf_size);
	ft_strdel(&info->buf);
	info->buf = new;
	info->nbr_mlc += 1;
}

static void	new_term_size(t_info *info, int fd)
{
	struct winsize w;

	ioctl(fd, TIOCGWINSZ, &w);
	info->max_line = w.ws_col;
	info->max_nbr_line = w.ws_row;
}

int			read_line(int fd, char **line)
{
	int		ret;
	t_info	info;

	if ((change_term_mode()) != 0)
		return (-1);
	init_struct(&info, fd);
	init_hist(&info);
	info.cur_hist = count_hist(&info.hist);
	while (1)
	{
		info.cur_pos == info.buf_max_size ? new_size(&info) : 0;
		new_term_size(&info, fd);
		ret = read(fd, &info.c, 1);
		if (ft_isprint(info.c))
			add_char(&info);
		if (which_key(fd, &info) == -1)
			break ;
	}
	maj_hist(&info);
	ft_putchar('\n');
	*line = info.buf;
	return (ret);
}
