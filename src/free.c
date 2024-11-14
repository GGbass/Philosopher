/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:48:58 by marvin            #+#    #+#             */
/*   Updated: 2024/11/14 23:07:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/* void	free_threads(t_data *data)
{
	int i;

	i = 0;
	while(i < data->philos->nb_philos)
	{
		pthread_detach(data->philos[i].threads);
		i++;
	}
} */

void	free_data(t_data *data)
{
	if (data->philos)
	{
		free(data->philos->threads);
		free(data->philos->forks);
		//pthread_destroy_mutex(data->philos->meal_mutex);
		//pthread_destroy_mutex(data->philos->sleep_mutex);
		//pthread_destroy_mutex(data->philos->write_mutex);
		free(data->philos);
	}
	free(data);
	exit(0);
}
