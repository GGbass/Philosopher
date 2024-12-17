/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 13:05:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	sleeping(t_philo *philos)
{
	print_thread(philos, philos->id, PHILO_SLEEP);
	ft_usleep(philos->time_to_sleep);
}

void	think(t_philo *philos)
{
	print_thread(philos, philos->id, PHILO_THINK);
}

void	take_forks(t_philo *philos)
{
	if (philos->id  == philos->nb_philos - 1)
	{
		pthread_mutex_lock(philos->left_fork);
		pthread_mutex_lock(philos->right_fork);
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		pthread_mutex_lock(philos->left_fork);
	}
}

int	is_dead(t_philo *philos)
{
	if ((int )get_time() - philos->last_meal >= philos->time_to_die)
	{
		philos->dead_flag = 1;
		return (1);
	}
	return (0);
}


int	eating(t_philo *philos)
{
	take_forks(philos);
	if (is_dead(philos))
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		return 0;
	}
	print_thread(philos, philos->id, PHILO_TAKE_FORK);
	print_thread(philos, philos->id, PHILO_EAT);
	ft_usleep(philos->time_to_eat);
	philos->last_meal = (int )get_time();
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	philos->times_each_must_eat--;
	return (1);
}

int	check_philos(t_philo *philos)
{
	if (philos->times_each_must_eat == 0)
		return (0);
	if (is_dead(philos) || philos->dead_flag == 1)
	{
		return (0);
	}
	return (1);
}

void	*routine(t_philo *philos)
{
	if (philos->id % 2 == 0)
		ft_usleep(10);
	philos->last_meal = (int )get_time();
	while(check_philos(philos))
	{
		if (philos->nb_philos == 1)
			ft_usleep(philos->time_to_die);
		if (!eating(philos))
		{
			print_thread(philos, philos->id, PHILO_DIE);
			return NULL;
		}
		sleeping(philos);
		think(philos);
		if (philos->times_each_must_eat == 0)
			 return NULL;
	}
	return NULL;
}
