/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:47:44 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 12:39:19 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	change_dir(t_node *head_env, char **cmd, char **path, char **old_path)
{
	if (cmd[1])
		*path = ft_strdup(cmd[1]);
	else
	{
		*path = ft_getenv("HOME", head_env);
		if (!(*path))
		{
			*old_path = ft_strdup("");
			return (print_error(NULL, ": HOME not set", 1));
		}
	}
	*old_path = getcwd(NULL, 1024);
	if (!*old_path && (!ft_strcmp(cmd[1], ".") || !ft_strcmp(cmd[1], "./")))
		return (cd_help (old_path, path, head_env));
	else
	{
		free(*old_path);
		change_dir_help(head_env, cmd[1], path, old_path);
	}
	return (0);
}

int	change_dir_help(t_node *head_env, char *cmd, char **path, char **old_path)
{
	char	*temp;

	*old_path = ft_getenv("PWD", head_env);
	if (*old_path == NULL)
	{
		temp = *old_path;
		*old_path = ft_strdup("");
		free(temp);
	}
	if (chdir(*path) == -1)
		return (print_error(cmd, ": No such file or directory", 1));
	free(*path);
	*path = getcwd(NULL, 1024);
	return (0);
}

void	set_value(char *str, char *value, t_node *head_env, char **cmd)
{
	t_node	*current;
	int		len;
	char	*temp;

	cmd = NULL;
	current = find(str, head_env);
	str = ft_strjoin(str, "=");
	temp = str;
	str = ft_strjoin(temp, value);
	free(temp);
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
	free(str);
}

int	cd_help(char **old_path, char **path, t_node *head_env)
{
	char	*temp;

	print_error(NULL, "cd: error retrieving current directory: getcwd:\
	cannot access parent directories: No such file or directory", 0);
	temp = *old_path;
	*old_path = ft_getenv("PWD", head_env);
	free(temp);
	if (!(*old_path))
		return (-1);
	temp = *old_path;
	*old_path = ft_strjoin(temp, "/");
	free(temp);
	temp = *path;
	*path = ft_strjoin(*old_path, *path);
	free(temp);
	return (0);
}

int	lbash_cd(char **cmd, t_node *head_env)
{
	char	*path;
	char	*old_path;
	int		ret;

	ret = change_dir(head_env, cmd, &path, &old_path);
	if (!ret)
	{
		set_value("OLDPWD", old_path, head_env, cmd);
		set_value("PWD", path, head_env, cmd);
	}
	free(path);
	free(old_path);
	return (ret);
}
