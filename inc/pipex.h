/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:16:03 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/10 10:06:18 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line_bonus.h"
# include <limits.h>
# include <sys/wait.h>
# include <stdbool.h>


void child_1(char **argv, char **envp, int *pipe_fd);
void child_2(char **argv, char **envp, int *pipe_fd);
void print_envp(char **envp);
void execute_command(char *cmd, char **envp);
char  *getpath(char *cmd1, char **envp);

#endif