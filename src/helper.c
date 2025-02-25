/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:15:16 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/18 16:00:21 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// splits the cmd1 or cmd2, searches the correct path 
//(try and error with access())
// executes in the correct path
void	execute_command(char *cmd, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	path = getpath(command[0], envp);
	if (path == NULL)
	{
		exit(EXIT_FAILURE);
	}
	execve(path, command, envp);
	return ;
}

// find in enviroment variable the path line 
// exclude "path" , spit each binary path and append the asked command,
//try each binary path to access
//return the correct binary path and free 
char	*getpath(char *cmd1, char **envp)
{
	char	**correct_path;
	char	*correct_path_with_cmd;
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	path = envp[i] + 5;
	correct_path = ft_split(path, ':');
	cmd1 = ft_strjoin("/", cmd1);
	i = -1;
	while ((correct_path[++i] != NULL))
	{
		correct_path_with_cmd = ft_strjoin(correct_path[i], cmd1);
		if (access(correct_path_with_cmd, X_OK) == 0)
		{
			free_splited_string(correct_path);
			return (correct_path_with_cmd);
		}
		free(correct_path_with_cmd);
	}
	free_splited_string(correct_path);
	ft_putendl_fd(cmd1, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_splited_string(char **splited_string)
{
	int	i;

	i = 0;
	while (splited_string[i] != NULL)
	{
		free(splited_string[i]);
		i++;
	}
	free(splited_string);
}

void	leaks(void)
{
	ft_printf("\n");
	system("leaks push_swap");
}
