/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 06:40:53 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	alive_status(t_philo *philos)
{
	pthread_mutex_lock(philos->dead);
	if (*philos->dead_flag == 1)
	{
		pthread_mutex_unlock(philos->dead);
		return (0);
	}
	pthread_mutex_unlock(philos->dead);
	return (1);
}

static int	sleeping(t_philo *philos)
{
	long starting_time;

	starting_time = get_time();
	print_thread(philos, philos->id, PHILO_SLEEP);
	while (1)
	{
		if (!alive_status(philos))
			return (0);
		if (get_time() - starting_time >= philos->time_to_sleep)
			return (1);
		usleep(100);
	}
	return (1);
}

void	take_forks(t_philo *philos)
{

	void	*first_fork;
	void	*second_fork;

	first_fork = NULL;
	second_fork = NULL;
	if (philos->id % 2 == 0)
	{
		first_fork = philos->right_fork;
		second_fork = philos->left_fork;
	}
	else
	{
		first_fork = philos->left_fork;
		second_fork = philos->right_fork;
	}	
	usleep(100);
	pthread_mutex_lock(first_fork);
	print_thread(philos, philos->id, PHILO_TAKE_FORK);
	pthread_mutex_lock(second_fork);
	print_thread(philos, philos->id, PHILO_TAKE_FORK);
}

void	release_forks(t_philo *philos)
{
	void	*first_fork;
	void	*second_fork;

	if (philos->id % 2)
	{
		first_fork = philos->right_fork;
		second_fork = philos->left_fork;
	}
	else
	{
		first_fork = philos->left_fork;
		second_fork = philos->right_fork;
	}
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

int	eating(t_philo *philos)
{
	if (!alive_status(philos))
		return (0);
	take_forks(philos);
	pthread_mutex_lock(philos->meal);
	philos->last_meal = get_time();
	philos->time_to_die = philos->last_meal + philos->ms_to_die;
	print_thread(philos, philos->id, PHILO_EAT);
	pthread_mutex_unlock(philos->meal);
	while(1)
	{
		if (!alive_status(philos))
			return (release_forks(philos), 0);
		if (get_time() - philos->last_meal >= philos->time_to_eat)
			break;
		usleep(100);
	}
	release_forks(philos);
	if (philos->times_each_must_eat > 0)
	{
		philos->times_each_must_eat--;
	}
	return (1);
}

void	*routine(void *philo)
{
	t_philo	*philos;
	
	philos = (t_philo *)philo;
	pthread_mutex_lock(philos->start);
	pthread_mutex_unlock(philos->start);
	while (alive_status(philos))
	{
		if (philos->nb_philos == 1)
		{
			pthread_mutex_lock(philos->left_fork);
			print_thread(philos, philos->id, PHILO_TAKE_FORK);
			ft_usleep(philos->time_to_die);
			pthread_mutex_unlock(philos->left_fork);
			return (NULL);
		}
		if (!eating(philos))
			return NULL;
		if (!sleeping(philos))
			return (NULL);
		if (!think(philos))
			return (NULL);
	}
	return (NULL);
}
