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
    char    *temp;

    if(cmd[1])
		*path = ft_strdup(cmd[1]);
    else
		*path = ft_strdup(getenv("HOME"));
	printf("path : %s\n", *path);
	*old_path = getcwd(NULL, 1024);
	printf("old_path : %s\n", *old_path);
	if (chdir(*path) != 0)
	{
		perror("PATH not exist or a file");
		return (1);
	}
	free(*path);
	*path = getcwd(NULL, 1024);
	return (0);
}

t_node	*set_value(char	*str, char	*value, t_node *head_env)
{
	char	*temp;
	int		len;
	
	temp = ft_strjoin(str, value);
	len = lenght(head_env);
	printf("TEMP :%s\n",temp);
	add_var(len, &head_env, temp);
	free(temp);
	return (head_env);
// 	current = find(str, *head_env);
// 	if (!current)
// 	{
// 		len = lenght(*head_env);
// 		temp = ft_strjoin(str, value);
// 		*head_env = insert(len, temp, *head_env);
// 	}
 }

int		lbash_cd(char **cmd, t_node *head_env)
{
  char  *path;
  char   *old_path;

  if (!change_dir(cmd, &path, &old_path))
  {
      head_env = set_value("OLDPWD=", old_path, head_env);
      head_env = set_value("PWD=", path, head_env);
  }
  free(path);
  free(old_path);
  // char cwd[256];
  return (lbash_env(head_env));
  // if (args[1] == NULL) {
  //   fprintf(stderr, "lbash: expected argument to \"cd\"\n");
  // }
  // else 
  // {
  //   if (chdir(args[1]) != 0) 
  //   {
  //     perror("lbash");
  //   }
  // }
  // printf("%s\n", getcwd(cwd, sizeof(cwd)));
  // return 1;
}

int     main(int argc, char **argv, char **envp)
{
    argc = 0;
    argv = 0;
    char *cmd[2];
	t_node *head;

    head = NULL;
	head = linked_list(head, envp);
	cmd[0] = "cd";
    cmd[1] = "../..";
    lbash_cd(cmd, head);
    printf("successful\n");
    return (0);
}
