/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:47:44 by ael-kass          #+#    #+#             */
/*   Updated: 2021/07/01 15:47:46 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int   change_dir(char **cmd, char **path, char **old_path)
{

    if(cmd[1])
		*path = ft_strdup(cmd[1]);
    else
		*path = ft_strdup(getenv("HOME"));
	*old_path = getcwd(NULL, 1024);
	if (chdir(*path) != 0)
		exit(print_error(cmd[1], ": No such file or directory", 1));
	free(*path);
	*path = getcwd(NULL, 1024);
	return (0);
}

void  set_value(char	*str, char	*value, t_node *head_env)
{
	char	*temp;
	t_node *current;
	int		len;

	current = find(str, head_env);
	temp = ft_strjoin(str, "=");
	str = temp;
	temp = ft_strjoin(str, value);
	free(str);
	if (!current)
	{
		len = lenght(head_env);
		insert(len, temp, head_env);
  	}
  	else
  	{
		//printf("Hello\n");
		free(current->data);
    	current->data = ft_strdup(temp);
	}
}

int		lbash_cd(char **cmd, t_node *head_env)
{
	char  *path;
	char   *old_path;

	if (!change_dir(cmd, &path, &old_path))
	{
		set_value("OLDPWD", old_path, head_env);
		set_value("PWD", path, head_env);
	}
	free(path);
	free(old_path);
	return (0);
}

// int     main(int argc, char **argv, char **envp)
// {
// 	argc = 0;
// 	argv = 0;
// 	char *cmd[2];
// 	t_node *head;

// 	head = NULL;
// 	head = linked_list(head, envp);
// 	cmd[0] = "cd";
// 	cmd[1] = "../..";
// 	lbash_cd(cmd, head);
// 	printf("successful\n");
// 	return (0);
// }
