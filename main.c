
#include "main.h"

int		main(void)
{
	char	*cmd_line;
	int		r;

/*
 * implement our basic REPL loop
 */
	while (1)
	{
		write(2, "minishell$ ", 12); // print prompt string
		r = get_next_line(0, &cmd_line);// read input from stdin
		if (r == -1)
			exit(EXIT_FAILURE);
		if (ft_strncmp(cmd_line, "exit", 5) == 0)
			break ;
		if (cmd_line[0] == '\0')// if user pressed ENTER without writing anything
			continue ;
		printf("%s\n", cmd_line);// print line and loop for next command
	}
	return (0);
}
