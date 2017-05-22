# include "minishell.h"

int main()
{
	char *line;

	line = NULL;
	while (1)
	{
		ft_putstr("$> ");
		read_line(0, &line);
		ft_putendl(line);
		if (ft_strcmp(line, "exit") == 0)
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}
