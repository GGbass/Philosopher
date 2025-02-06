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

void	*philo_routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->data->forks);
		sem_wait(philo->data->forks);
		sem_wait(philo->data->print);
		printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
		printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
		sem_post(philo->data->print);
		sem_wait(philo->data->print);
		printf("%ld %d is eating\n", get_time() - philo->data->start_time, philo->id);
		sem_post(philo->data->print);
		philo->last_meal = get_time();
		usleep(philo->data->time_to_eat * 1000);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		sem_wait(philo->data->print);
		printf("%ld %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
		sem_post(philo->data->print);
		usleep(philo->data->time_to_sleep * 1000);
		sem_wait(philo->data->print);
		printf("%ld %d is thinking\n", get_time() - philo->data->start_time, philo->id);
		sem_post(philo->data->print);
	}
	return (NULL);
}
