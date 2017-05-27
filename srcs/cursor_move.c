#include "minishell.h"

void	arrow_left(t_info *info)
{
	if (info->cur_pos > 0)
	{
		info->cur_pos--;
		ft_putstr("\033[1D");
	}
}

void	arrow_right(t_info *info)
{
//	if (info->cur_pos == info->char_max)
//	{
		/* GERER LE NBR DE LIGNE */
//	}
	if (info->cur_pos < ft_strlen(info->buf))
		ft_putstr("\033[1C");
	info->cur_pos++;
}
