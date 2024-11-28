/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/27 01:24:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	take_forks(t_philo *philos)
{

	if (philos->id + 1 % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		pthread_mutex_lock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_EAT);
		pthread_mutex_lock(philos->meal_mutex);
		philos->last_meal = (int )get_time();
		pthread_mutex_unlock(philos->meal_mutex);
		print_thread(philos, philos->id, PHILO_SLEEP);
		ft_usleep(philos->time_to_sleep);
	}
	else if (philos->id  == philos->nb_philos - 1)
	{
		pthread_mutex_lock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		pthread_mutex_lock(philos->right_fork);
		print_thread(philos, philos->id, PHILO_EAT);
		pthread_mutex_lock(philos->meal_mutex);
		philos->last_meal = (int )get_time();
		pthread_mutex_unlock(philos->meal_mutex);
		print_thread(philos, philos->id, PHILO_SLEEP);
		ft_usleep(philos->time_to_sleep);
	}
/* 	else if (philos->id % 2 == 0)
	{
		printf("a loj \n");
		print_thread(philos, philos->id, PHILO_SLEEP);
		ft_usleep(philos->time_to_sleep);
	} */
	if (philos->nb_philos + 1 % 2 != 0)
	{
		printf("id left forks %d\n", philos->id);
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
	else if (philos->id == philos->nb_philos - 1)
	{
		printf("id left forks %d\n", philos->id);
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
}

int	eating(t_philo *philos)
{
	print_thread(philos, philos->id, PHILO_THINK);
	take_forks(philos);
	return (1);
}

int	is_dead(t_philo *philos)
{
	pthread_mutex_lock(philos->meal_mutex);
	if ((int )get_time() - philos->last_meal >= philos->time_to_die)
	{
		philos->dead_flag = 1;
		pthread_mutex_unlock(philos->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(philos->meal_mutex);
	return (0);
}

int	check_philos(t_philo *philos)
{
	if (philos->times_each_must_eat == 0)
		return (0);
	pthread_mutex_lock(&philos->dead_mutex);
	if (is_dead(philos) || philos->dead_flag == 1)
	{
		pthread_mutex_unlock(&philos->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philos->dead_mutex);
	return (1);
}

void	*routine(t_philo *philos)
{
	pthread_mutex_lock(&philos->philo_begin);
	pthread_mutex_unlock(&philos->philo_begin);
	if (philos->id % 2 == 0)
		ft_usleep(100);
	while(!check_philos(philos))
	{
		printf("id 0 %d\n", philos[0].id);
		printf("id 1 %d\n", philos[1].id);
		if (philos->id % 2 == 0)
			ft_usleep(100);
		if (philos->nb_philos == 1)
		{
			ft_usleep(philos->time_to_die);
		}
		if (!eating(philos))
		{
			printf("%ld %d %s\n", get_time(), philos->id, PHILO_DIE);
			return NULL;
		}
		if (philos->times_each_must_eat == 0)
			 return NULL;
	}
	return NULL;
}
