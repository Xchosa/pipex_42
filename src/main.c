/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:19:20 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/04 12:00:37 by poverbec         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	int	fd[2];
	int	pid_1;
	int pid_2;
	int res;
	int test;
	test = atoi(argv[1]);
	if (argc == 2)
	// if ((argc != 5) || *(argv[1]))
		// return(EXIT_FAILURE);
	
	if	(pipe(fd) == -1)
		return (ft_putstr_fd("Error, executing pipe", STDERR_FILENO), EXIT_FAILURE);
	pid_1 = fork();
	if(pid_1 == -1)
		return (ft_putstr_fd("Error, forking", STDERR_FILENO), EXIT_FAILURE);
	if(pid_1 == 0)
	{
		ft_printf("its a child_1\n");
		ft_printf("process id %d\n", pid_1);
		ft_printf("test child_1 %d\n", test);
	}
	wait(NULL);// waits for the childprocess to finish 
	if (pid_1 != 0)
	{
		res = wait(NULL);
		ft_printf("parent process 1 %d \n", res);
	}
	pid_2 = fork();
	if (pid_2 == -1)
		return (ft_putstr_fd("Error, forking", STDERR_FILENO), EXIT_FAILURE);
	if (pid_2 == 0)
	{
		ft_printf("its a child_2\n");
		ft_printf("process id %d\n", pid_2);
		ft_printf("test child_2 %d\n", test);
	}
	if (pid_2 != 0)
		ft_printf("parent 2 res id %d\n", res);
	
}

	// void child_1()
	// {
	// 	"infile.txt", O_RDONLY | O_CREAT;
	// }

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
