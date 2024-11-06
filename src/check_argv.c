/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:33:04 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:33:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_chars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_argv(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc != 5 || argc != 6)
	{
		perror("Error: wrong number of arguments\n", 2);
		return (0);
	}
	while(i < argc)
	{
		if (ft_atoi(argv[i]) < 0 || !check_chars(argv[i]))
		{
			perror("Error: arguments must be positive integers\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
