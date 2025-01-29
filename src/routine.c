/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/29 23:05:37 by gongarci         ###   ########.fr       */
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
	if (!alive_status(philos))
		return (0);
	/* if (*philos->dead_flag == 1)
		return (0); */
	print_thread(philos, philos->id, PHILO_SLEEP);
	//printf("time to sleep + current %d >= %d \n", philos->time_to_sleep + (int)get_time(), philos->time_to_die);
/* 	if (philos->time_to_sleep + get_time() >= philos->time_to_die)
	{
		ft_usleep(philos->time_to_die - get_time());
	}
	else
		ft_usleep(philos->time_to_sleep); */
	ft_usleep(philos->time_to_sleep);
	return (1);
}

void	take_forks(t_philo *philos)
{
	if (philos->id % 2)
	{
		pthread_mutex_lock(philos->left_fork);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		printf("%p\n", philos->left_fork);
		pthread_mutex_lock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		printf("%p\n", philos->right_fork);
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		printf("%p\n", philos->right_fork);
		pthread_mutex_lock(philos->left_fork);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		printf("%p\n", philos->left_fork);
	}
}

void	release_forks(t_philo *philos)
{
	if (philos->id % 2 == 1)
	{
		pthread_mutex_unlock(philos->right_fork);
		//print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		//printf("%p\n", philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		//print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		//printf("%p\n", philos->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork);
		//print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		//printf("%p\n", philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		//print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		//printf("%p\n", philos->right_fork);
	}
}


int	eating(t_philo *philos)
{
	if (!alive_status(philos))
		return (0);
	take_forks(philos);
	if (philos->nb_philos == 1)
	{
		release_forks(philos);
		ft_usleep(philos->time_to_die);
		return (0);
	}
	pthread_mutex_lock(philos->meal);
	print_thread(philos, philos->id, PHILO_EAT);
	philos->last_meal = get_time();
	pthread_mutex_lock(philos->dead);
	philos->time_to_die = philos->last_meal + philos->ms_to_die;
	pthread_mutex_unlock(philos->dead);
	ft_usleep(philos->time_to_eat);
	pthread_mutex_unlock(philos->meal);
	release_forks(philos);
	if (philos->times_each_must_eat != -1)
		philos->times_each_must_eat--;
	return (1);
}

void	*routine(void *philo)
{
	t_philo	*philos;
	
	philos = (t_philo *)philo;
	//ft_usleep(5);
	pthread_mutex_lock(philos->start);
	pthread_mutex_unlock(philos->start);
	if (philos->id % 2 == 1)
			ft_usleep(philos->time_to_eat);
	while (alive_status(philos))
	{
		if (philos->id % 2 == 0)
			ft_usleep(2);
		if (!eating(philos))
			return NULL;
		if (!sleeping(philos))
			return (NULL);
		if (!think(philos))
			return (NULL);
		if (philos->times_each_must_eat == 0 || *philos->dead_flag == 1)
			return (NULL);
	}
	return (NULL);
}
