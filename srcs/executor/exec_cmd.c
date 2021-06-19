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

#include "../../includes/main.h"
#include "../../includes/executor.h"

int     free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
    return(-1);
}

char    *get_path(char *path, char **envp)
{
    int		i;
	char	**temp;
	

	temp = NULL;
	i = -1;
	//printf()
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

char	*add_char(char *str, char c)
{
	int		len;
	char	*temp;
	
	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	temp = malloc ((len + 2) * sizeof(char));
	if (!temp)
		return (NULL);
	if (len)
		ft_strlcpy(temp, str, len + 1);
	temp[len++] = c;
	temp[len] = '\0';
	//free_array(&str);
	return (temp);
}

char    *find_path(char *envp[], char **cmd, int i)
{
    char    **temp;
	char	*temp1;
    char    *dst;
    struct stat buffer;

   // dst = get_path("PATH", envp);
   (void)envp;
    dst = getenv("PATH");
	//printf("SDJKFFASLHD :: %s\n", dst);
    if (!dst)
        return (NULL);
    temp = ft_split(dst, ':');
    while (temp[++i])
    {
        //printf("TEMP ::%s\n", temp[i]);
		temp1 = temp[i];
		temp[i] = add_char(temp[i], '/');
		free(temp1);
		//printf("temp%s\n", temp[i]);
		temp1 = ft_strjoin(temp[i], cmd[0]);
        if (!lstat(temp1, &buffer))
            return (temp1);
		free(temp1);
    }
    free_array(temp);
    // execute_cmd(temp1, envp, cmd);
	//printf("PATH %s\n", temp1);
    return(NULL);
}

void    execute_cmd(char *path, char **envp, char **cmd)
{
        if (execve(path, cmd, envp) == -1)
            perror("could not execve");
}