
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"


typedef struct s_node
{
    char     *data;
    struct s_node *next;
}       t_node;

typedef struct s_env
{
    char    *var;
    char    *value;
}       t_env;


void	visitor_visit(t_ast *node, t_node *head_env);
int		lbash_cd(char **cmd, t_node *head_env);
int		check_n(char *args, int *flag);
int		lbash_echo(char **args);
int		lbash_env(t_node *head_env);
int		lbash_exit(char **cmd);
void	sort_env(t_node	*head);
int		lenght(t_node	*current);
void    printenv_expor(t_node	*head);
int     add_var(int n, t_node *head, char *cmd);
t_node  *insert(int n, char *data, t_node *head);
t_node	*find(char *str, t_node *head);
int     lbash_export(t_node *head_env, char **cmd);
int     lbash_pwd(void);
int     lbash_unset(t_node *head, char **cmd);
void	printlist(t_node *head);
int		free_array(char **array);
char	*find_path(char **cmd, int i);
int		execute_cmd(t_node *head_env, int last_fd, int fds[], char **cmd, t_ast *pipecmd, int totalPipe);
char	*get_path(char *path, char **envp);
char	*add_char(char *str, char c);
int		is_builtin(char *str);
int		built_in(char  **cmd, t_node *head_env);
t_node  *linked_list(t_node *head, char **env);
int		start_exec(t_node *head_env, t_ast **pipecmd, int index, int last_fd, int num_size);
char	**convert_list(t_node *head_env);
int     is_builtin1(char *str);
int		correct_var(const char *var);
int     process(t_node *head_env, t_ast *pipecmd, int *last_fd, int totalPipe, int fds[]);
int     printf_error(char *cmd, char *str, int	error);
void	get_return_stat(int ret, int flag);

#endif
