/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 14:14:23 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/29 19:47:47 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	mode_normal(void)
{

}
*/
void	mode_raw(void)
{
	struct termios new;

	if (tcgetattr(0, &new) == -1)
		ft_putendl("tcgeattr error");
	new.c_lflag &= ~(ICANON | ECHO);
	new.c_lflag = 0;
	if (tcsetattr(0, TCSANOW, &new) == -1)
		ft_putendl("tcsetattr error");
}

int		main(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		mode_raw();
		ft_putstr("$> ");
		read_line(0, &line);
		ft_putstr("\nline = ");
		ft_putendl(line);
		if (ft_strcmp(line, "exit") == 0)
			break ;
		ft_strdel(&line);
		ft_putchar('\n');
	}
	ft_strdel(&line);
	return (0);
}
