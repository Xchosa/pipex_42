/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:50:29 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/11 15:18:42 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
The	isalnum(void) method returns True if all characters 
in the string are alphanumeric (either 
alphabets or numbers). If not, it returns False.
*/

int	ft_isalnum(int a)
{
	if (ft_isdigit(a) != '\0' || (ft_isalpha(a) != '\0'))
	{
		return (1);
	}
	return (0);
}
