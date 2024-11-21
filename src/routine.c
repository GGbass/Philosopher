/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/21 21:58:26 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	next_fork(t_philo *philos)
{
	// replicar un trylock o crear una variable cual sera el mutex;
	if (philos->id + 1 < philos->nb_philos)
	{
		if (pthread_mutex_trylock(&philos->forks[philos->id + 1]) == 0 && philos->id != philos->nb_philos)
		{
			pthread_mutex_unlock(&philos->forks[philos->id + 1]);
			return 1;
		}
	}
	return 0;
}

void	take_forks(t_philo *philos)
{
	int	lock;

	lock = 0;
	pthread_mutex_lock(&philos->forks[philos->id]);
	if (pthread_mutex_lock(&philos->forks[philos->id + 1]) == 0 && philos->id != philos->nb_philos)
	{
		lock = 1;
		//check for next fork
		// 
		print_thread(philos, philos->id, PHILO_TAKE_FORK);
		print_thread(philos, philos->id, PHILO_EAT);
		pthread_mutex_lock(&philos->meal_mutex);
		philos->last_meal = (int )get_time();
		pthread_mutex_unlock(&philos->meal_mutex);
	}
	else if (!pthread_mutex_lock(&philos->forks[philos->id]))
	{
		printf("thinking\n");
		print_thread(philos, philos->id, PHILO_THINK);
	}
	else
	{
		print_thread(philos, philos->id, PHILO_SLEEP);
		ft_usleep(philos->time_to_sleep);
	}
	pthread_mutex_unlock(&philos->forks[philos->id]);
	if (lock == 1)
		pthread_mutex_unlock(&philos->forks[philos->id + 1]);
}

int	eating(t_philo *philos)
{
	take_forks(philos);
	return (1);
}

int	is_dead(t_philo *philos)
{
	pthread_mutex_lock(&philos->meal_mutex);
	if ((int )get_time() - philos->last_meal >= philos->time_to_die)
	{
		philos->dead_flag = 1;
		pthread_mutex_unlock(&philos->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->meal_mutex);
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
	if (philos->id % 2 == 0)
		ft_usleep(100);
	pthread_mutex_lock(&philos->philo_begin);
	pthread_mutex_unlock(&philos->philo_begin);
	while(!check_philos(philos))
	{
		printf("philo \n");
		if (philos->id % 2 != 0)
			ft_usleep(100);
		if (philos->nb_philos == 1)
		{
			ft_usleep(philos->time_to_die);
			return (NULL);
		}
		if (!eating(philos))
		{
			printf("%ld %d %s\n", get_time(), philos->id, PHILO_DIE);
			return (NULL);
		}
		//if (philos->times_each_must_eat == 0)
		//	return (NULL);
		//sleeping(philos);
		//thinking(philos);
	}
	return (philos);
}
