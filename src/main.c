/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:19:20 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/08 11:36:50 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

#include <stdio.h> 

// exclude stdio.h 
/*
./pipex file1 cmd1 cmd2 file2
It must take 4 arguments:
• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters
*/


void print_envp(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void ft_command_one(char **argv, char **envp)
{
	char **command;
	command = ft_split(*argv, ' ');
	ft_printf("what input ? %s \n", command);
	print_envp(envp);
	ft_printf("commant content %s",command);
}

void child_1(char **argv, char **envp, int *pipe_fd)
{
	int error;
	error = open(argv[1], O_RDONLY);
	if(error == -1)
	{
		return; //(ft_putstr_fd("Could not Read file", STDERR_FILENO), EXIT_FAILURE);
		close(pipe_fd[0]); 
		close(pipe_fd[1]);
	}
	//fflush(STDOUT_FILENO);
	ft_printf("input of file %s", argv[2]);
	// envp takes 3 argu path to eexecutable , array of argument strings, array of envirom strings. 
	ft_command_one(&argv[2], envp);
	
}

// void child_2(char **argv, char **envp, int *pipe_fd)// gets stdout of cmd2 written in file2, if not existing file gets created
// {
// 	int error;
// 	error = open(argv[1], O_RDONLY | O_CREAT);

// }




int main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid_1;
	int pid_2;
	int res;
	if (argc == 2)
	// if ((argc != 5) || *(argv[1]))
		// return(EXIT_FAILURE);
	
	if (pipe(pipe_fd) == -1)
		return (ft_putstr_fd("Error, executing pipe", STDERR_FILENO), EXIT_FAILURE);
	pid_1 = fork(); // 
	if (pid_1 == -1)
		return (ft_putstr_fd("Error, forking", STDERR_FILENO), EXIT_FAILURE);
	if (pid_1 == 0)
	{
		ft_printf("child process process id %d\n", pid_1);
		child_1(argv, envp, pipe_fd);// cmd reads its input from file1 instead of keyboard 
	}
	if (pid_1 != 0) // parent process has to wait until child is finished 
	{
		res = wait(NULL);
		ft_printf("parent process 1 %d \n", res);
	}
	pid_2 = fork();
	if (pid_2 == -1)
		return (ft_putstr_fd("Error, forking", STDERR_FILENO), EXIT_FAILURE);
	if (pid_2 == 0)
	{
		ft_printf("process id of child %d\n", pid_2);
	}
	if (pid_2 != 0)
		{
			int res2;
			res2 = wait(NULL);
			ft_printf("parent 2 res id %d\n", res2);
		}
	close(pipe_fd[1]);
	print_envp(envp); 
}




// 	((argv[1]), O_RDONLY);
// 	// if (input == -1);
// 	// 	return (ft_putstr_fd("Could not Read file", STDERR_FILENO), EXIT_FAILURE);
// 	// pipe(fd);
// 	int pid = fork();
// 		// int res = wait(NULL);
// 	ft_printf("whats is first ");
// 	fflush(STDOUT_FILENO);
// 	wait(NULL);
// 		// ft_printf(" res %d\n", res);
	
// 	if(pid == 0)
// 	{
// 		ft_printf("its a child\n");
// 		ft_printf("process id %d\n", pid);
// 		sleep(5);
// 	}
// 	else
// 	{
// 		wait(NULL);// immer auf child process 
// 		ft_printf("its the parent\n");
// 		ft_printf("%d\n", pid);
// 	}
// }
