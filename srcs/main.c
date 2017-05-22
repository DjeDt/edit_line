# include "minishell.h"

int main()
{
	int count;
	char *line;

	line = NULL;
	while (1)
	{
		count= 0;
		ft_putstr("$> ");
		read_line(0, &line);
		ft_putstr("line = ");
		ft_putendl(line);
		ft_putendl("line decompose :");
		while (line[count] != '\0')
		{
			ft_putstr("-");
			ft_putchar(line[count]);
			count++;
			ft_putchar('\n');
		}
		if (ft_strcmp(line, "exit") == 0)
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}
