/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:10:29 by marvin            #+#    #+#             */
/*   Updated: 2025/02/11 19:00:59 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static int	thinking(t_data *data)
{
	if (!check_alive(data))
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
		if (!check_alive(data))
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
	if (!check_alive(data))
		return (0);
	take_or_release_forks(data, 0);
	sem_wait(data->meal);
	data->last_meal = get_time();
	printf("step 1 \n");
	print_action(data, data->philos->id, PHILO_EAT);
	while(1)
	{
/* 		if (!check_alive(data))
			return (take_or_release_forks(data, 1), 0); */
		if (get_time() - data->last_meal >= data->time_to_eat)
			break ;
		usleep(100);
	}
	take_or_release_forks(data, 1);
	sem_post(data->meal);
	if (data->times_each_must_eat > 0)
	{
		data->times_each_must_eat--;
		if (data->times_each_must_eat == 0)
		{
			(*data->finished)++;
			return (0);
		}
	}
	return (1);
}

void	*philo_routine(t_data *data, int id)
{
	data->philos->id = id;
	sem_wait(data->start);
	sem_post(data->start);
	data->last_meal = get_time();
	data->time_start = get_time();
	while (check_alive(data))
	{
		if (data->nb_philos == 1)
		{
			sem_wait(data->forks);
			print_action(data, data->philos->id, PHILO_TAKE_FORK);
			ft_usleep(data->time_to_die);
			sem_post(data->forks);
			print_action(data, data->philos->id, PHILO_DIE);
			return (NULL);
		}
		if (data->philos->id % 2 == 0)
			usleep(100);
		if (!eating(data))
			return (NULL);
		if (!sleeping(data))
			return (NULL);
		if (!thinking(data))
			return (NULL);
	}
	exit(1);
}
