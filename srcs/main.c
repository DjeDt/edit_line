/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 18:08:25 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/10 18:13:12 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		ft_putstr("$> ");
		read_line(0, &line);
		if (ft_strcmp("exit", line) == 0)
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	return (0);
}
