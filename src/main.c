/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:19:20 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/18 16:14:38 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
./pipex file1 cmd1 cmd2 file2
// ls gets malloced , cant be freed. 
// execute path envp cant be freed its reachable 
./pipex infile "grep a1" "wc -w" outfile
*/
// redirects infilde_fd and replaces it with stdin (input from console)
// pipe output/ write end becomes the stdout  
// close the read end of the pipe/ input
//Data written to the write end of the pipe is buffered by the kernel 
//until it is read from the read end of the pipe
void	child_1(char **argv, char **envp, int *pipe_fd)
{
	int	infile_fd;

	close(pipe_fd[0]);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exit (EXIT_FAILURE);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_command(argv[2], envp);
}

//  gets stdout of cmd2 written in file2, if not existing file gets created
// name of outputfile, open file for writing only, creat if not exiting, 
// truncated file to zero length, if it exists alreadyy
// file perm read , write for owner, read -only for others
void	parent(char **argv, char **envp, int *pipe_fd)
{
	int	output_fd;

	close(pipe_fd[1]);
	output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_1;

	if ((argc != 5) || (argv[2]) == NULL || argv[3] == NULL)
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	pid_1 = fork();
	if (pid_1 == -1)
		return (EXIT_FAILURE);
	if (pid_1 == 0)
	{
		child_1(argv, envp, pipe_fd);
	}
	else
	{
		parent(argv, envp, pipe_fd);
		if (waitpid(pid_1, 0, 0) < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
