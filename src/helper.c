/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:15:16 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/10 12:24:22 by poverbec         ###   ########.fr       */
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
	// its already checked if the file is readable 
	
	command = ft_split(cmd, ' ');
	// execute Command 
	char *path;
	
	//access(/usr/local/bin/ls, 3)
	path = getpath(command[0], envp);// command 0 is 'ls -l"and search for 
	ft_printf("\n \n what path %s \n", path);// print in the pipe 
	if (execve(path, command, envp) == -1)
	// does not return if successful 
	// process image is replaced by the new programm 
		return;
		
	// her find path and counting it 
	// output gives 4 
// ./pipex infile "grep a1" "wc -w" outfile
// < infile grep a1 | wc -w > outfile
// update git ignore file with inflie and outfile 
	
	//If command[0] is "grep", then execve() 
	//will attempt to execute grep as a new program, replacing the current process
	ft_printf("\n \n what input ? %s \n", command);
	print_envp(envp);
	
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
		i ++;
		ft_printf("path %s\n",path);
	}
	path += 5; //without path= 
	ft_printf("\n correct path in envp: %s \n ", path);
	
	correct_path = ft_split(path, ':');// in the path line 2D array
	cmd1= ft_strjoin("/", cmd1);
	ft_printf(" correct command %s\n", cmd1);
	i = 0;
	ft_printf(" correct path %s\n", correct_path[i]);
	while((access(correct_path_with_cmd, X_OK) != 0))
	{
		correct_path_with_cmd = ft_strjoin(correct_path[i], cmd1);// user/bin und ls -l 
		ft_printf(" correct command %s\n", correct_path_with_cmd);
		if(access(correct_path_with_cmd, X_OK) != 0))
			correct_path_with_cmd++;
	}
	return (*correct_path);
}

