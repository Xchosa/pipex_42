/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:15:16 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/11 13:10:23 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void print_envp(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void execute_command(char *cmd, char **envp)
{
	char **command;
	command = ft_split(cmd, ' ');
	char *path;
	
	path = getpath(command[0], envp);// command 0 is 'ls -l"and search for 
	if(path == NULL)
	{
		ft_putstr_fd( "cmd not fould\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	
	execve(path, command, envp);
	return;
}

char  *getpath(char *cmd1, char **envp)
{
	char **correct_path;
	char *correct_path_with_cmd;
	
	int i = 0;
	char *path = envp[i];
	while (ft_strncmp("PATH=", path , 5) != 0)
	{
		path = envp[i];
		i++;
	}
	// ft_printf("path %s\n",path);
	path += 5; //without path= 
	// ft_printf("\n correct path in envp: %s \n ", path);
	
	correct_path = ft_split(path, ':');// in the path line 2D array
	cmd1= ft_strjoin("/", cmd1);
	// ft_printf("correct command:  %s\n", cmd1);
	i = 0;
	while((correct_path[i] != NULL))
	{
		correct_path_with_cmd = ft_strjoin(correct_path[i], cmd1);// user/bin und ls -l 
		// ft_printf(" access path with correct command?:\n %s\n", correct_path_with_cmd);
		if(access(correct_path_with_cmd, X_OK) == 0)
		{
			// char *cpy_correct_path;
			// cpy_correct_path = ft_strdup(correct_path_with_cmd[i]);
			free_splited_string(correct_path);
			return (correct_path_with_cmd);;
		}
		free(correct_path_with_cmd);
		i++;
	}
	free_splited_string(correct_path);
	return (NULL);
}

void	free_splited_string(char **splited_string)
{
	int i;
	i = 0;
	while(splited_string[i] != NULL)
	{
		free(splited_string[i]);
		i++;
	}
	free(splited_string);
}

