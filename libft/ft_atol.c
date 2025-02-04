/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:16:33 by poverbec          #+#    #+#             */
/*   Updated: 2025/01/29 15:54:30 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"


long	ft_atol(char *str)
{
	int		isneg;
	int		i;
	long	number;
	int		valid;

	number = 0;
	i = 0;
	isneg = 1;
	valid = 0;
	while (str[i] == (' ') || ((str[i] >= 9) && str[i] <= 13))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i++] == '-')
			isneg *= -1;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		valid = 1;
		number = number * 10 + (str[i++] - '0');
	}
	if (valid == 0 || str[i] != '\0')
		return (LONG_MIN);
	return (number * isneg);
}
