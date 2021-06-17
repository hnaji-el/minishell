
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

int		visitor_visit(t_ast *node);
void	visitor_visit_compound(t_ast *node);
void	visitor_visit_pipeline(t_ast *node);
void	visitor_visit_command(t_ast *node);
void	visitor_visit_redirection(t_redirect *node);

#endif
