/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:02:42 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/10 18:06:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"

typedef struct		s_hist
{
	int				cur;
	char			*value;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_info
{
	char			c;
	char			*buf;
	int				buf_size;
	int				nbr_mlc;
	int				cur_pos;
	int				buf_max_size;
	int				max_nbr_line;
	int				current_line;
	int				min_line;
	int				max_line;
	int				cur_hist;
	int				max_hist;
	int				hist_fd;
	char			*save_buf;
	t_hist			*hist;
}					t_info;

int					read_line(const int fd, char **line);

int					change_term_mode(void);
int					raw_mode(struct termios *prev);
int					normal_mode(struct termios *prev);

int					which_key(int fd, t_info *info);

int					arrow_left(t_info *info);
int					arrow_right(t_info *info);
void				go_to_end(t_info *info);
void				go_to_begin(t_info *info);

void				key_delete(t_info *info);
void				key_delete_rev(t_info *info);
void				add_char(t_info *info);

t_hist				*create_hist(const char *str, int cur);
int					read_hist(const int fd, char **buf);
void				free_hist(t_hist **hist);
void				init_hist(t_info *info);
void				add_hist(const char *str, int cur, t_hist **hist);
int					count_hist(t_hist **hist);
void				maj_hist(t_info *info);
void				save_current_buf(t_info *info);
int					history_up(t_info *info, t_hist **hist);
int					history_down(t_info *info, t_hist **hist);

#endif
