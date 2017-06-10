/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:50:17 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/10 16:11:13 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_hist		*create_hist(const char *str, int cur)
{
	t_hist	*ret;

	ret = NULL;
	if (!(ret = (t_hist*)malloc(sizeof(t_hist))))
		return (NULL);
	if (str != NULL)
	{
		ret->cur = cur;
		ret->value = ft_strdup(str);
	}
	else
	{
		ret->cur = 0;
		ret->value = NULL;
	}
	ret->next = NULL;
	return (ret);
}

void		add_hist(const char *str, int cur, t_hist **hist)
{
	t_hist	*tmp;

	tmp = NULL;
	if (!(*hist))
		(*hist) = create_hist(str, cur);
	else
	{
		tmp = (*hist);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_hist(str, cur);
	}
}

void		init_hist(t_info *info)
{
	int		cur;
	char	*tmp;

	cur = 0;
	tmp = NULL;
	while (get_next_line(info->hist_fd, &tmp))
	{
		if (tmp == NULL)
			return ;
		add_hist(tmp, cur, &info->hist);
		ft_strdel(&tmp);
		info->max_hist += 1;
		cur++;
	}
}

int			count_hist(t_hist **hist)
{
	int		count;
	t_hist	*tmp;

	if (*hist == NULL)
		return (0);
	count = 0;
	tmp = *hist;
	while (tmp->next != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void		free_hist(t_hist **hist)
{
	t_hist	*tmp;

	tmp = *hist;
	while (tmp->next != NULL)
	{
		ft_strdel(&tmp->value);
		free(tmp);
		tmp = tmp->next;
	}
	ft_strdel(&tmp->value);
	free(tmp);
}
