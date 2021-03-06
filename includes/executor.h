/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:45:29 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 17:52:01 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}				t_node;

typedef struct s_exec
{
	int		last_fd;
	int		fds[2];
	int		totalPipe;
}				t_exec;

void	visitor_visit(t_ast *node, t_node **head_env);
int		lbash_cd(char **cmd, t_node *head_env);
int		check_n(char **args);
int		lbash_echo(char **args);
int		lbash_env(t_node *head_env, char **cmd);
int		lbash_exit(char **cmd);
void	sort_env(t_node	*head, int i, int j, int count);
int		lenght(t_node	*current);
void	printenv_expor(t_node	*head, int out_fd, char *str, int count);
int		add_var(int n, t_node *head, char *cmd);
t_node	*insert(int n, char *data, t_node *head);
t_node	*find(char *str, t_node *head);
int		lbash_export(t_node *head_env, char **cmd, int out_fd);
int		lbash_pwd(void);
int		lbash_unset(t_node **head, char **cmd);
void	printlist(t_node *head);
int		free_array(char **array);
char	*find_path(char **cmd, int i, t_node *head_env);
int		execute_cmd(t_node **head_env, t_exec *exec, char **cmd,
			t_ast *pipecmd);
char	*get_path(char *path, char **envp);
char	*add_char(char *str, char c);
int		is_builtin(char *str);
int		built_in(char **cmd, t_node **head_env, int flag, t_ast *pipecmd);
t_node	*linked_list(t_node *head, char **env);
int		start_exec(t_node **head_env, t_ast **pipecmd,
			t_exec *exec, int num_size);
char	**convert_list(t_node *head_env);
int		is_builtin1(char *str);
int		correct_var(const char *var);
int		process(t_node **head_env, t_ast *pipecmd, t_exec *exec);
int		print_error(char *cmd, char *str, int	error);
void	get_return_stat(int ret, int flag);
int		delet_var(t_node **head, char *cmd);
int		cd_help(char **old_path, char **path, t_node *head_env);
int		get_file_fd(int *last_fd, int *out_fd, t_ast *pipecmd,
			t_node *head_env);
int		change_dir_help(t_node *head_env, char *cmd, char **path,
			char **old_path);
int		get_out_fd(t_redirect red, int *out_fd);
int		get_here_doc(t_redirect red, int *last_fd, t_node *head_env);
int		get_in_fd(t_redirect red, int *last_fd);

#endif
