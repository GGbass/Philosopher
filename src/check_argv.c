/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:33:04 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 11:10:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

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
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		write(2, "./philo [number of philos], [time to die], [time to eat], [time to sleep]", 73);
		write(2, " and [times to eat before ends the program]\n", 44);
		return (0);
	}
	while(i < argc)
	{
		if (ft_atoi(argv[i]) < 0 || ft_atoi(argv[1]) > 200)
		{
			write(2, "Error: Negatives or more than 200 threads are not allowed\n", 58);
			return (0);
		}
		if (!check_chars(argv[i]))
		{
			write(2, "Error: arguments must be positive integers\n", 44);
			return (0);
		}
		i++;
	}
	return (1);
}
