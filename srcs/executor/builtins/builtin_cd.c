/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:47:44 by ael-kass          #+#    #+#             */
/*   Updated: 2021/09/30 11:57:03 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	change_dir(t_node *head_env, char **cmd, char **path, char **old_path)
{
	if (cmd[1])
		*path = ft_strdup(cmd[1]);
	else
	{
		*path = ft_strdup(ft_getenv("HOME", head_env));
		if (!(*path))
			return (-1);
	}
	*old_path = getcwd(NULL, 1024);
	if (!*old_path && (!ft_strcmp(cmd[1], ".") || !ft_strcmp(cmd[1], "./")))
		return(cd_help(old_path, path, head_env));
	else
	{
		*old_path = ft_getenv("PWD", head_env);
		if (chdir(*path) != 0)
			print_error(cmd[1], ": No such file or directory", 1);
		free(*path);
		*path = getcwd(NULL, 1024);
	}
	return (0);
}

void  set_value(char	*str, char	*value, t_node *head_env, char **cmd)
{
	t_node *current;
	int		len;

	cmd = NULL;
	current = find(str, head_env);
	str = ft_strjoin(str, "=");
	str = ft_strjoin(str, value);
	if (!current)
	{
		len = lenght(head_env);
		insert(len, str, head_env);
	}
	else
	{
		free(current->data);
		current->data = ft_strdup(str);
	}
}

int		cd_help(char **old_path, char **path, t_node *head_env)
{
	// char *temp;

	print_error(NULL,
			"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 0);
		// temp = *old_path;
		// free(temp);
		*old_path = ft_getenv("PWD", head_env);
		// temp = *old_path;
		*old_path = ft_strjoin(*old_path, "/");
		// free(temp);
		// temp = *path;
		*path = ft_strjoin(*old_path, *path);
		// free(temp);
	return (0);
}

int		lbash_cd(char **cmd, t_node *head_env)
{
	char  *path;
	char   *old_path;

	if (!change_dir(head_env, cmd, &path, &old_path))
	{
		set_value("OLDPWD", old_path, head_env, cmd);
		set_value("PWD", path, head_env, cmd);
		free(path);
		free(old_path);
	}
	return (0);
}

