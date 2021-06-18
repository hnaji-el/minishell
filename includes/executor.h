
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"


typedef struct s_node
{
    char     *data;
    struct s_node* next;
}       t_node;

typedef struct s_env
{
    char    *var;
    char    *value;
}       t_env;


int		visitor_visit(t_ast *node, char **envp);
void	visitor_visit_compound(t_ast *node, char **envp);
void	visitor_visit_pipeline(t_ast *node, char **envp);
void	visitor_visit_command(t_ast *node, char **envp);
void	visitor_visit_redirection(t_redirect *node);
int		lbash_cd(char **args);
int		check_n(char *args, int *flag);
int		lbash_echo(char **args);
int		lbash_env(char **envp);
int		lbash_exit(char **cmd);
void	sort_env(t_node	*head);
int		lenght(t_node	*current);
void    printenv_expor(t_node	*head);
void	add_var(int n, t_node **head, char *cmd);
t_node	*insert(int n, char *data, t_node *head);
t_node	*find(char *str, t_node *head);
t_node	*lbash_export(char *envp[], char **cmd);
int     lbash_pwd(void);
t_node	*lbash_unset(t_node **head, char **cmd);
void	printlist(t_node *head);
int		free_array(char **array);
char	*find_path(char *envp[], char **cmd);
void	execute_cmd(char *path, char **envp, char **cmd);

#endif
