/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:59:41 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/04 11:01:03 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static int	check_chars(char *str)
{
	int	i;

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
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		write(2, "./philo [n philos], [time to die], [time to eat],", 49);
		write(2, "[time to sleep] and [times each philo has to eat]\n", 50);
		return (0);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0 || ft_atoi(argv[1]) > 200)
		{
			write(2, "Error: Negatives or more than 200 threads\n", 43);
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
