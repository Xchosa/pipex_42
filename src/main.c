/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:19:20 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/04 10:21:04 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// https://medium.com/@lannur-s/pipex-42-chapter-1-metamorphosis-execve-1a4710ab8cb1

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		int input;
		input = ft_atoi(argv[1]);
		int fd[2];
		pipe(fd);
		int pid = fork();
		// int res = wait(NULL);
		wait(NULL);
		// ft_printf(" res %d\n", res);
		
		if(pid == 0)
		{
			ft_printf("its a child\n");
			ft_printf("process id %d\n", pid);
			sleep(5);
		}
		else
		{
			wait(NULL);// immer auf child process 
			ft_printf("its the parent\n");
			ft_printf("%d\n", pid);
		}
	}
}
