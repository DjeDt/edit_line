/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:02:42 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/30 15:55:31 by ddinaut          ###   ########.fr       */
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
	char	*buf;
	size_t	buf_size;

	size_t	cur_pos;

	size_t	buf_max_size;
	size_t	char_max_by_line;

	size_t	begin_line;
	size_t	current_line;

	size_t min_line;
	size_t max_line;

	}			t_info;

int		read_line(const int fd, char **line);
void	mode_raw(void);
void	mode_normal(void);

/* Cursor move */
void	which_key(int fd, t_info *info);

void	arrow_left(t_info *info);
void	arrow_right(t_info *info);
void	go_to_end(t_info *info);
void	go_to_begin(t_info *info);

void	arrow_del(t_info *info);
void	arrow_rev_del(t_info *info);
void	add_char(t_info *info);


#endif
