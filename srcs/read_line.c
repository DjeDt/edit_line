/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:47:22 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/25 20:52:00 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_struct(t_info *info, int fd)
{
	struct winsize w;

	ioctl(fd, TIOCGWINSZ, &w);

	info->char_max = w.ws_col;
	info->len_max = w.ws_col;
	info->nb_line = w.ws_row;
	info->cur_pos = 0;
	info->c = 0;

//	info->fd = fopen("/Users/ddinaut/Desktop/edit_line/log.log", "w+");
	info->fd = fopen("log.log", "w+");

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
	fprintf(info->fd, "\n\nFonction new size :\n");
	fprintf(info->fd, "- info->len max = %zu\n- nbr = %d\n", info->len_max, nbr);
	if (!(new = malloc(sizeof(char) * info->len_max - 2))) // pareil que pour init struct
	{
		ft_putendl("error malloc new_size");
		exit (-1);
	}
	ft_bzero(new, info->len_max);
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
	while (1)
	{
		fprintf(info.fd, "buf = %s\n", info.buf);
		if (info.cur_pos == (size_t)info.len_max)
			new_size(&info);
		ret = read(fd, &info.c, 1);
		if (info.c == 10)
			break ;
		if (ft_isprint(info.c))
			add_char(&info);
		if (info.c == 27)
			which_key(fd, &info);
	}
	info.buf[info.cur_pos] = '\0';
	*line = info.buf;
	return (ret);
}
