/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:24:21 by marvin            #+#    #+#             */
/*   Updated: 2024/11/13 14:24:21 by marvin           ###   ########.fr       */
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