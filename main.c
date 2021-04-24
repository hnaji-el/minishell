
#include "main.h"

int		main(void)
{
	char	*cmd_line;
	int		r;

	while (1)
	{
		write(2, "minishell$ ", 12);

	}
	return (0);
}

int		main(void)
{
	char	*cmd_line;
	int		r;

   	/*
	 * implement our basic REPL LOOP
	 */
	while (1)
	{
		write(2, "minishell$ ", 12); // print shell prompt
		r = get_next_line(0, &cmd_line); // read input from stdin
		if (r == -1)
			break ;
		if (cmd[0] == '\n') // if user pressed ENTER without writing anything
			continue ;
		if (!ft_strncmp(cmd, "exit\n", 6))
			break ;
		printf("%s", cmd); // print line and loop for next command
	}
	return (0);
}
