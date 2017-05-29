/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:47:22 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/26 17:48:55 by ddinaut          ###   ########.fr       */
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

	info->fd = fopen("log.log", "w+");

	fprintf(info->fd, "fonction init struct :\nchar_max = %d\nlen_max = %zu\nb_line = %d\n", info->char_max, info->len_max, info->nb_line);
	if (!(info->buf = (char*)malloc(sizeof(char) * info->char_max - 2))) // - 2 == + 1 - 3 -> (- 3 pour la taille du prompt)
	{
		ft_putendl("error malloc init struct");
		exit (-1);
	}
	ft_bzero(info->buf, info->char_max - 2);
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

static void	new_line(t_info *info)
{
	info->cur_pos = 0;
	info->nb_line += 1;

	ft_putstr("/033[")
}

int		read_line(int fd, char **line)
{
	int		ret;
	t_info	info;

	init_struct(&info, fd);
	while (1)
	{
		fprintf(info.fd, "debut boucle readline: buf = %s\n", info.buf);
		info.cur_pos == (size_t)info.len_max ? new_size(&info) : 0;
		info.cur_pos == (size_t)info.char_max ? new_line(&info) : 0;
		ret = read(fd, &info.c, 1);
		if (info.c == 10)
			break ;
		if (ft_isprint(info.c))
			add_char(&info);
		if (info.c == 27)
			which_key(fd, &info);
		if (info.c == 127)
			arrow_del(&info);
		fprintf(info.fd, "fin de boucle readline: buf = %s\n", info.buf);
	}
	*line = info.buf;
	return (ret);
}
