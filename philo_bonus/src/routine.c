/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:10:29 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 21:15:18 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static int	thinking(t_data *data)
{
	if (!alive_status(data))
		return (0);
	print_action(data, data->philos->id, PHILO_THINK);
	return (1);
}

static int	sleeping(t_data *data)
{
	long	start;

	start = get_time();
	if (!alive_status(data))
		return (0);
	print_action(data, data->philos->id, PHILO_SLEEP);
	while (1)
	{
		if (!alive_status(data))
			return (0);
		if (get_time() - start >= data->time_to_sleep)
			break ;
		usleep(10);
	}
	return (1);
}

static void	take_or_release_forks(t_data *data, int release_flag)
{
	if (!release_flag)
	{
		usleep(50);
		sem_wait(data->forks);
		print_action(data, data->philos->id, PHILO_TAKE_FORK);
		sem_wait(data->forks);
		print_action(data, data->philos->id, PHILO_TAKE_FORK);
	}
	else
	{
		if (data->philos->id % 2 == 0)
			usleep(50);
		sem_post(data->forks);
		sem_post(data->forks);
	}
}

static int	eating(t_data *data)
{
	if (!alive_status(data))
		return (0);
	take_or_release_forks(data, 0);
	sem_wait(data->meal);
	data->last_meal = get_time();
	print_action(data, data->philos->id, PHILO_EAT);
	sem_post(data->meal);
	while (1)
	{
		if (!alive_status(data))
			return (take_or_release_forks(data, 1), 0);
		if (get_time() - data->last_meal >= data->time_to_eat)
			break ;
		usleep(15);
	}
	take_or_release_forks(data, 1);
	sem_wait(data->start);
	if (!meals_check(data))
		return (0);
	sem_post(data->start);
	return (1);
}

void	*philo_routine(t_data *data)
{
	sem_wait(data->start);
	data->last_meal = get_time();
	data->time_start = get_time();
	if (pthread_create(&data->monitorer, NULL, monitor, (void *)data))
		(free_data(data), exit(1));
	sem_post(data->start);
	while (1)
	{
		if (data->nb_philos == 1)
		{
			take_or_release_forks(data, 0);
			break ;
		}
		usleep(20);
		if (!eating(data))
			break ;
		if (!sleeping(data))
			break ;
		if (!thinking(data))
			break ;
	}
	pthread_join(data->monitorer, NULL);
	return (NULL);
}
