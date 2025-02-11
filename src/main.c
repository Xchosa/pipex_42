/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:19:20 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/11 13:11:09 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

#include <stdio.h> 

// exclude stdio.h 
/*
./pipex file1 cmd1 cmd2 file2


./pipex infile "grep a1" "wc -w" outfile
*/


void child_1(char **argv, char **envp, int *pipe_fd)
{
	int infile_fd;
	close(pipe_fd[0]); 
	infile_fd = open(argv[1], O_RDONLY);// 0 und 1 belegt wird zu 3
	if(infile_fd == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return;//(ft_putstr_fd("Could not Read file", STDERR_FILENO), EXIT_FAILURE);
	}
	
	dup2(infile_fd, STDIN_FILENO);// redirects infilde_fd and replaces it with stdin (input from console)
	close(infile_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	// pipe output/ write end becomes the stdout  
	close(pipe_fd[1]);// close the read end of the pipe/ input
	execute_command(argv[2], envp);
	//Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe
}

void parent(char **argv, char **envp, int *pipe_fd)// gets stdout of cmd2 written in file2, if not existing file gets created
{
	int output_fd;
	close(pipe_fd[1]);
	output_fd = open(argv[4], O_WRONLY| O_CREAT | O_TRUNC, 0644 );
	// name of outputfile, open file for writing only, creat if not exiting, truncated file to zero length, if it exists alreadyy
	// file perm read , write for owner, read -only for others
	if( output_fd == -1)
	{
		close(pipe_fd[0]);// read pipe / stdin
    	close(pipe_fd[1]); // write pipe / stdout
    	exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);// read vom pipe
	close(pipe_fd[0]);// read pipe / stdin
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	execute_command(argv[3], envp); // execude second cmd
}



int main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid_1;
	if ((argc != 5) || (argv[2])== NULL || argv[3] == NULL)
		return(EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		return (ft_putstr_fd("Error, executing pipe", STDERR_FILENO), EXIT_FAILURE);
	pid_1 = fork(); // 
	if (pid_1 == -1)
		return (perror("Error, forking"),EXIT_FAILURE);
	if (pid_1 == 0)
	{
		child_1(argv, envp, pipe_fd);// cmd reads its input from file1 instead of keyboard 
	}
	else
	{	
		wait(NULL);
		parent(argv, envp, pipe_fd);
	}
}

