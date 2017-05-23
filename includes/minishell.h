/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:02:42 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/19 15:02:45 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/stat.h>
# include <signal.h>

# include <termios.h>

typedef struct	s_info
{
	size_t	cur_pos;
	int		term_max;
	char	*buf;
}				t_info;

int		read_line(const int fd, char **line);
void	mode_raw(void);
void	mode_normal(void);

/* arrow */
void	arrow_left();
void	arrow_right();
void	arrow_delete();
void	which_arrow(int fd);

#endif
