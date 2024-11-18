/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:24:21 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 18:09:08 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	philo_and_fork_assigner(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->philos->nb_philos)
	{
		data->philos->threads[i] = i;
		i++;
	}
	i = 0;
	while (i < data->philos->nb_philos)
	{
		pthread_mutex_init(&data->philos->forks[i], NULL);
		i++;
	}
}

void	thread_values(t_data *data)
{
	int i;

	i = 0;
	while(i < data->philos->nb_philos)
	{
		data->philos[i].id = i;
		data->philos[i].time_to_eat = data->philos->time_to_eat;
		data->philos[i].time_to_sleep = data->philos->time_to_sleep;
		data->philos[i].time_to_die = data->philos->time_to_die;
		data->philos[i].nb_philos = data->philos->nb_philos;
		data->philos[i].times_each_must_eat = data->philos->times_each_must_eat;
		i++;
	}
}
