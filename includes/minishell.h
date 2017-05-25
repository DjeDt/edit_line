/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:02:42 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/25 19:34:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>

/* pour log  */
# include <stdio.h>
//FILE	*fd;
/* Fin du log */

typedef struct	s_info
{
	FILE	*fd;
	char	c;
	size_t	cur_pos;
	size_t	len_max;
	int		char_max;
	int		nb_line;
	char	*buf;
}				t_info;

int		read_line(const int fd, char **line);
void	mode_raw(void);
void	mode_normal(void);

/* arrow */
void	arrow_left(t_info *info);
void	arrow_right(t_info *info);
void	arrow_delete(t_info *info);
void	add_char(t_info *info);
void	which_key(int fd, t_info *info);

#endif
