/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:48:58 by marvin            #+#    #+#             */
/*   Updated: 2025/01/11 19:30:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	mutex_cleanup(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->dead);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	mutex_cleanup(data);
	if (data->forks)
	{
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			data->philos[i].left_fork = NULL;
			data->philos[i].right_fork = NULL;
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	free(data);
	exit(0);
}
