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

// void    set_command(char *key, char *value, char *envp, t_env   **env)
// {
//     // (*env)->var = key;
//     // if (env)
//     // {
//     //     while (env)
//     //     {
//     //         /* code */
//     //         if (!ft_strcmp(key, (*env)->var))
//     //             break;
            
//     //     }
        
//     // }
//     if (ft_strcmp(key, "PATH") == 0)
//     {
//         return (1);
//     }
// }

char    *find_path(char *envp[], char **cmd)
{
    char    **temp;
    char    *dst;
    struct stat buffer;
    int     i;

    dst = NULL;
    i = 0;
    // while (*envp)
    // {
       //printf("ENVP: %s\n", *envp);
        dst = getenv("PATH");
        temp = ft_split(dst, '=');
        free_array(&dst);
        if (temp)
        {
            printf("PATH PATH PATH  ");
            while (temp[1] != NULL)
            {
                printf("HERE HERE HERE\n");
                temp = ft_split(temp[1], ':');
                dst = ft_strjoin(temp[0], cmd[0]);
                //free_array((void **)temp);
                free(dst);
                printf("LSTAT %d\n", lstat(dst, &buffer));
                if (lstat(dst, &buffer) == 0)
                    return (dst);
                // temp++;
            }
            // if (*temp == NULL)
            //     EXIT_FAILURE;
        }
        free_array(temp);
        execute_cmd(dst, envp, cmd);
       // envp++;
       // i++;
   // }
    return (dst);
}

void    execute_cmd(char *path, char **envp, char **cmd)
{
        if (execve(path, cmd, envp) == -1)
            perror("could not execve");
}

// int     main(int argc, char *argv[], char *envp[])
// {
//     char    *cmd = "ls";
//     char    *path;
//     t_env   *env;

//     path = find_path(envp, env, cmd);
//     execute_cmd(path, envp, &cmd);
//     //args
// }
