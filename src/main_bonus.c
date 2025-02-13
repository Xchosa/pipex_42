/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:30:01 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/13 15:05:29 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

//Should behave like:
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// Support « and » when the first parameter is "here_doc".
// $> ./pipex here_doc LIMITER cmd cmd1 file

//Should behave like:
// cmd << LIMITER | cmd1 >> file

void encounter_cmd(char **argv, int *pipe_fd)
{
	int infile_fd;
	infile_fd = open(argv, O_RDONLY);
	if (infile_fd == -1)
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exit (EXIT_FAILURE);
	dup2_function(infile_fd, pipe_fd);
}
void dup2_function (int infile_fd, int *pipe_fd)
{
	dup2(infile_fd, STDIN_FILENO);
	// close(infile_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	// close(pipe_fd[1]);
	
}
	
void create_pipe()
{
	
}

// int error_func(int nbr)
// {
// 	if(nbr == -1)
// 		close()
// }

int main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		i;
	pid_t	pid_1;

	i = 1;
	if ((argc < 5) || argc > 15 || (argv[i]) == NULL)
		return (EXIT_FAILURE);
	encounter_cmd(argv +i, pipe_fd);
	while (i < argc -1 )
	{
		create_pipe()
	}
		
}