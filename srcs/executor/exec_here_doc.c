/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:34:54 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/25 22:58:09 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*collect_env_var(char *here_doc, int *i, t_node *envp_ll)
{
	char	*fr;
	char	*str;
	int		index_i;
	int		index_f;

	index_i = *i;
	while (here_doc[*i] == '_' || ft_isalnum(here_doc[*i]))
		*i += 1;
	index_f = *i;
	str = ft_substr(here_doc, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	fr = str;
	str = ft_getenv(str, envp_ll);
	if (str == NULL)
		str = ft_strdup_("");
	free(fr);
	return (str);
}

char    *collect_env_vars_in_here_doc(char *here_doc, int *i, t_node *envp_ll)
{
    char    *str;

	*i += 1;
	if (here_doc[*i] == '?')
	{
		str = ft_itoa(127); // exit_status : global variable
		if (str == NULL)
			put_error(errno);
		*i += 1;
	}
	else if (here_doc[*i] != '_' && !ft_isalpha(here_doc[*i]))
	{
		str = ft_substr(here_doc, (*i) - 1, 2);
		if (str == NULL)
			put_error(errno);
		*i += 1;
	}
	else
		str = collect_env_var(here_doc, i, envp_ll);
    return (str);
}

char    *collect_simple_characters(char *here_doc, int *index)
{
    char    *str;
    int     index_i;
    int     index_f;

    index_i = *index;
    while (here_doc[*index] != '\0' && here_doc[*index] != '$')
        (*index)++;
    index_f = *index;
	str = ft_substr(here_doc, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
    return (str);
}

void    exec_expansion_and_put_line(char *here_doc, int *fd, t_node *envp_ll)
{
    char    *str;
    int     i;

    i = 0;
    while (here_doc[i] != '\0')
    {
        if (here_doc[i] == '$')
            str = collect_env_vars_in_here_doc(here_doc, &i, envp_ll);
        else
            str = collect_simple_characters(here_doc, &i);
        ft_putstr_fd(str, *fd);
        free(str);
    }
    write(*fd, "\n", 1);
}

void    exec_here_doc(int *fd, char *delimiter, t_red_type type, t_node *envp_ll)
{
    char    *here_doc;

    while (1)
    {
		here_doc = readline("> ");
        if (!ft_strcmp(here_doc, delimiter))
            break ;
        if (type == RED_HERE_DOC)
            ft_putendl_fd(here_doc, *fd);
        if (type == RED_HERE_DOC_EXP)
            exec_expansion_and_put_line(here_doc, fd, envp_ll);
        free(here_doc);
    }
    free(here_doc);
}
