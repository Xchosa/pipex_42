/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:15:16 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/08 16:44:09 by poverbec         ###   ########.fr       */
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

void execute_command(char **cmd, char **envp)
{
	char **command;
	// its already checked if the file is readable 
	

	
	command = ft_split(*cmd, ' ');
	// execute Command 
	if (execve(command[0], command, envp) == -1)
	// does not return if successful 
	// process image is replaced by the new programm 
		return;
	
	//If command[0] is "grep", then execve() 
	//will attempt to execute grep as a new program, replacing the current process
	ft_printf("\n \n what input ? %s \n", command);
	print_envp(envp);
	ft_printf("\n \n command content %s\n \n ",command);
	
}

