/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:10:29 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 23:10:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void	*philo_routine(t_data *data)
{
	while (1)
	{
		sem_wait(data->forks);
		print_action(data, data->philos->id, PHILO_TAKE_FORK);
		sem_wait(data->forks);
		print_action(data, data->philos->id, PHILO_TAKE_FORK);
		sem_wait(data->meal);
		print_action(data, data->philos->id, PHILO_EAT);
		sem_post(data->meal);
		data->last_meal = get_time();
		ft_usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		print_action(data, data->philos->id, PHILO_SLEEP);
		ft_usleep(data->time_to_sleep);
		print_action(data, data->philos->id, PHILO_THINK);
	}
	return (NULL);
}
