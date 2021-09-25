/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 10:06:42 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/25 23:08:03 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/* strerror() and printf() function */
# include <stdio.h>

/* my own libft and get_next_line */
# include "../srcs/libft/libft.h"

/* GNU Readline Library */
# include <readline/readline.h>
# include <readline/history.h>

/* signal() and kill() system call functions */
# include <signal.h>

/* open() function */
# include <fcntl.h>

/* read() and write() and close() functions */
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

/* malloc() and free() exit() function */
# include <stdlib.h>

/* errno external variable */
# include <sys/errno.h>

# include <string.h>
# include <sys/stat.h>

#endif
