/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:31:40 by ael-kass          #+#    #+#             */
/*   Updated: 2021/06/18 19:31:55 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (-1);
}

char *get_path(char *path, char **envp)
{
	int i;
	char **temp;

	temp = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strcmp(path, envp[i]))
		{
			temp = ft_split(envp[i], '=');
			return (temp[1]);
		}
	}
	return (NULL);
}

char *add_char(char *str, char c)
{
	int len;
	char *temp;

	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	temp = malloc((len + 2) * sizeof(char));
	if (!temp)
		return (NULL);
	if (len)
		ft_strlcpy(temp, str, len + 1);
	temp[len++] = c;
	temp[len] = '\0';
	return (temp);
}

char	**convert_list(t_node *head_env)
{
	t_node	*current;
	int		len;
	int		i;
	char	**str;

	// find  the length of the
	// given linked list
	if (head_env == NULL)
		return (NULL);
	len = lenght(head_env);

	//Creat aan array
	str = malloc((len + 1) * sizeof(char *));
	current = head_env;
	//  Traverse the linked List and add the
	// elements to the array one by one
	i = 0;
	while (current != NULL)
	{
		str[i++] = ft_strdup(current->data);
		current = current->next;
	}
	str[i] = NULL;
	return (str);
}

char *find_path(char **cmd, int i, t_node *head_env)
{
	char **temp;
	char *temp1;
	char *dst;
	struct stat buffer;

	if (!lstat(cmd[0], &buffer) && !S_ISDIR(buffer.st_mode) && (buffer.st_mode & S_IXUSR))
			return (cmd[0]);
	dst = ft_getenv("PATH", head_env);
	if (!dst)
		return (NULL);
	temp = ft_split(dst, ':');
	while (temp[++i])
	{
		temp1 = temp[i];
		temp[i] = add_char(temp[i], '/');
		free(temp1);
		temp1 = ft_strjoin(temp[i], cmd[0]);
		if (!lstat(temp1, &buffer) && !S_ISDIR(buffer.st_mode) && (buffer.st_mode & S_IXUSR))
			return (temp1);
		free(temp1);
	}
	free_array(temp);
	return (NULL);
}

int		execute_cmd(t_node **head_env, int last_fd, int fds[], char **cmd, t_ast *pipecmd, int totalPipe)
{
	char **env;

	dup2(last_fd, 0);
	if(last_fd)
		close(last_fd);
	if (totalPipe < pipecmd->pipe_size || pipecmd->flag == 1)
		 dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	env = convert_list(*head_env);
	if (is_builtin(cmd[0]) == -1)
	{
		if (!execve(*cmd, cmd, env))
		{
			free_array(env);
			perror("could not execve");
			return(1);
		}
		free_array(env);
	}
	else
		built_in(cmd, head_env, 0, pipecmd);
	free_array(env);
	return(0);
}