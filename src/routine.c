/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/27 23:26:07 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	sleeping(t_philo *philos)
{
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
/* 	if (philos->id % 2 == 0 && philos->nb_philos % 2)
	{
		pthread_mutex_lock(philos->right_fork);
		pthread_mutex_lock(philos->print);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		pthread_mutex_unlock(philos->print);
		printf("%p\n", philos->right_fork);
		pthread_mutex_lock(philos->left_fork);
		pthread_mutex_lock(philos->print);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		pthread_mutex_unlock(philos->print);
		printf("%p\n", philos->left_fork);

	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		pthread_mutex_lock(philos->print);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		pthread_mutex_unlock(philos->print);
		printf("%p\n", philos->left_fork);
		pthread_mutex_lock(philos->right_fork);
		pthread_mutex_lock(philos->print);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		pthread_mutex_unlock(philos->print);
		printf("%p\n", philos->right_fork);
	} */
}

void	release_forks(t_philo *philos)
{
	if (philos->id % 2 == 1)
	{
		pthread_mutex_unlock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->right_fork);
	}
/* 	if (philos->id % 2 == 0  && philos->nb_philos % 2)
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_lock(philos->print);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->right_fork);
		pthread_mutex_unlock(philos->print);
	}
	else
	{
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_lock(philos->print);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		print_thread(philos, philos->id, PHILO_RELEASE_FORK);
		printf("%p\n", philos->left_fork);
		pthread_mutex_unlock(philos->print);
	} */
}


int	eating(t_philo *philos)
{
		take_forks(philos);
/* 	if (!check_philo(philos) || *philos->dead_flag == 1)
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		return (0);
	} */
	if (*philos->dead_flag == 1)
	{
		ft_usleep(philos->time_to_die);
		release_forks(philos);
		return (0);
	}
	pthread_mutex_lock(philos->meal);
	print_thread(philos, philos->id, PHILO_EAT);
	pthread_mutex_unlock(philos->meal);
	philos->last_meal = get_time();
	philos->time_to_die = philos->last_meal + philos->ms_to_die;
	ft_usleep(philos->time_to_eat);
	release_forks(philos);
	if (philos->times_each_must_eat != -1)
		philos->times_each_must_eat--;
	return (1);
}

void	*routine(t_philo *philos)
{
	ft_usleep(5);
	philos->start_time = get_time();
	philos->last_meal = philos->start_time;
	philos->ms_to_die = philos->time_to_die;
	philos->time_to_die = philos->last_meal + philos->ms_to_die;
	if (philos->id % 2 == 1)
			ft_usleep(philos->time_to_eat);
	while (!*philos->dead_flag)
	{
		if (philos->id % 2 == 0)
			ft_usleep(2);
		eating(philos);
		sleeping(philos);
		think(philos);
		if (philos->times_each_must_eat == 0)
			return (NULL);
	}
	return (NULL);
}
