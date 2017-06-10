/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_term_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 13:40:26 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/08 18:38:16 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	error_mode(const char *func, const char *sub_func)
{
	ft_putstr_fd("error in func: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(sub_func, 2);
	ft_putendl_fd("setting on basic edit_line.", 2);
	return (-1);
}

int			normal_mode(struct termios *prev)
{
	return (tcsetattr(0, TCSANOW, prev));
}

int			raw_mode(struct termios *prev)
{
	struct termios new;

	if (tcgetattr(0, prev) == -1)
		return (error_mode("mode_raw: ", "with tcgetattr: "));
	if (tcgetattr(0, &new) == -1)
		return (error_mode("mode_raw: ", "with tcgetattr: "));
	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &new) == -1)
		return (error_mode("mode raw: ", "with tcsetattr: "));
	return (0);
}

int			change_term_mode(void)
{
	struct termios prev;

	if (raw_mode(&prev) != 0)
	{
		normal_mode(&prev);
		return (-1);
	}
	return (0);
}
