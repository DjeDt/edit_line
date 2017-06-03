/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:02:42 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/03 22:46:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>

# include <stdio.h> // Pour log

typedef struct	s_info
{
	FILE		*fd;

	char		c;
	char		*buf;
	int			buf_size;
	int			nbr_mlc;
	int			cur_pos;
	int			buf_max_size;
	int			begin_line;
	int			current_line;
	int			min_line;
	int			max_line;
}				t_info;

int				read_line(const int fd, char **line);
void			mode_raw(void);
void			mode_normal(void);

void			which_key(int fd, t_info *info);

int				arrow_left(t_info *info);
int				arrow_right(t_info *info);
void			go_to_end(t_info *info);
void			go_to_begin(t_info *info);

void			arrow_del(t_info *info);
void			arrow_rev_del(t_info *info);
void			add_char(t_info *info);

#endif
