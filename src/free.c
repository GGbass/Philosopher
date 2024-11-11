/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:48:58 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 19:58:09 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free_data(t_data *data)
{
	if (data->philos)
	{
		free(data->philos->threads);
		free(data->philos->forks);
		free(data->philos->forks_status);
		free(data->philos->forks_time);
		//pthread_destroy_mutex(data->philos->meal_mutex);
		//pthread_destroy_mutex(data->philos->sleep_mutex);
		//pthread_destroy_mutex(data->philos->write_mutex);
		free(data->philos);
	}
	free(data);
	exit(0);
}
