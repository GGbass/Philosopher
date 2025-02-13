/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:10:29 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 22:16:48 by gongarci         ###   ########.fr       */
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
	print_action(data, data->philos->id, PHILO_SLEEP);
	while(1)
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
		sem_wait(data->forks);
		print_action(data, data->philos->id, PHILO_TAKE_FORK);
		usleep(10);
		sem_wait(data->forks);
		print_action(data, data->philos->id, PHILO_TAKE_FORK);
	}
	else
	{
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
	while(1)
	{
		if (!alive_status(data))
			return (take_or_release_forks(data, 1), 0);
		if (get_time() - data->last_meal >= data->time_to_eat)
			break ;
		usleep(10);
	}
	sem_wait(data->meal);
	take_or_release_forks(data, 1);
	if (data->times_each_must_eat > 0)
	{
		data->times_each_must_eat--;
		if (data->times_each_must_eat == 0)
		{
			(*data->finished)++;
			return (sem_post(data->meal), 0);
		}
	}
	sem_post(data->meal);
	return (1);
}

void	*philo_routine(t_data *data, int id)
{
	data->philos->id = id;
	sem_wait(data->start);
	sem_post(data->start);
	data->last_meal = get_time();
	data->time_start = get_time();
	if (pthread_create(&data->monitorer, NULL, monitor, (void *)data))
		(free_data(data), exit(1));
	while (alive_status(data))
	{
		if (data->nb_philos == 1)
		{
			sem_wait(data->forks);
			print_action(data, data->philos->id, PHILO_TAKE_FORK);
			ft_usleep(data->time_to_die);
			sem_post(data->forks);
			print_action(data, data->philos->id, PHILO_DIE);
			break ;
		}
		if (data->philos->id % 2 == 0)
			usleep(5);
		if (!eating(data))
			break ;
		if (!sleeping(data))
			break ;
		if (!thinking(data))
			break ;
	}
	pthread_join(data->monitorer, NULL);
	if (data->times_each_must_eat == 0)
		exit(0);
	exit(1);
}
