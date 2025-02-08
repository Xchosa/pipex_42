/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:19:20 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/08 16:37:40 by poverbec         ###   ########.fr       */
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


void child_1(char **argv, char **envp, int *pipe_fd)
{
	int infile_fd;
	infile_fd = open(argv[1], O_RDONLY);
	if(infile_fd == -1)
	{
		return; //(ft_putstr_fd("Could not Read file", STDERR_FILENO), EXIT_FAILURE);
		close(pipe_fd[0]); 
		close(pipe_fd[1]);
	}
	//fflush(STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);// duplicates infilde_fd and replaces it with stdin (input from console)
	//stdin reads now from infilde_fd 
	close(infile_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	// pipe output/ write end becomes the stdout  
	
	close(pipe_fd[0]);// close the read end of the pipe/ input
	close(pipe_fd[1]);// close the write end of the file/ output
	execute_command(&argv[2], envp);
	//Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe
}

void child_2(char **argv, char **envp, int *pipe_fd)// gets stdout of cmd2 written in file2, if not existing file gets created
{
	int output_fd;
	output_fd = open(argv[4], O_WRONLY| O_CREAT | O_TRUNC, 0644 );
	// name of outputfile, open file for writing only, creat if not exiting, truncated file to zero length, if it exists alreadyy
	// file perm read , write for owner, read -only for others
	if( output_fd == -1)
	{
		close(pipe_fd[0]);// read pipe / stdin
    	close(pipe_fd[1]); // write pipe / stdout
    	exit(EXIT_FAILURE);
	}
	dup2(output_fd, STDIN_FILENO);// copys the input of the before to the file
	
	close(pipe_fd[0]);// read pipe / stdin
    close(pipe_fd[1]); // write pipe / stdout
	dup2(output_fd, STDOUT_FILENO);
	execute_command(&argv[3], envp); // execude second cmd
}



int main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid_1;
	int pid_2;
	int res;
	int res2;
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
		int id = getpid();
		ft_printf("child process process id %d\n", id);
		child_1(argv, envp, pipe_fd);// cmd reads its input from file1 instead of keyboard 
	}
	res = wait(NULL);
	if (pid_1 != 0) // parent process has to wait until child is finished 
	{
		ft_printf("parent 1 process  %d \n", res);
	}
	pid_2 = fork();
	if (pid_2 == -1)
		return (ft_putstr_fd("Error, forking", STDERR_FILENO), EXIT_FAILURE);
	if (pid_2 == 0)
	{
		ft_printf("process id of child %d\n", pid_2);
		child_2(argv, envp, pipe_fd);
	}
	res2 = wait(NULL);
	if (pid_2 != 0)
		{
			ft_printf("parent 2 res id %d\n", res2);
		}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
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
