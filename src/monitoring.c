/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:43:45 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/04 06:40:09 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	time_checker(t_philo *philos)
{
	//printf("Philosopher %d last meal: %zu and time to die %zu\n", philos->id, philos->last_meal, philos->time_to_die);
	pthread_mutex_lock(philos->meal);
	if (get_time() > philos->time_to_die)
	{
		//printf("result: %zu\n", get_time() - philos->time_to_die);
		pthread_mutex_unlock(philos->meal);
		return (0);
	}
	pthread_mutex_unlock(philos->meal);
	return (1);
}

static int	aux_eat(t_philo *philos)
{
	pthread_mutex_lock(philos->meal);
	if (philos->times_each_must_eat == -1 || !alive_status(philos))
		return (pthread_mutex_unlock(philos->meal), 1);
	pthread_mutex_unlock(philos->meal);
	return (0);
}

static int	everyone_ate(t_philo *philos)
{
	int i;
	int ate;

	i = 0;
	ate = 0;
	if (aux_eat(philos))
		return (1);
	while (i < philos->nb_philos)
	{
		pthread_mutex_lock(philos->meal);
		if (philos[i].times_each_must_eat == 0)
			ate++;
		pthread_mutex_unlock(philos->meal);
		pthread_mutex_lock(philos->dead);
		if (ate == philos->nb_philos)
		{
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			return (0);
		}
		pthread_mutex_unlock(philos->dead);
		printf("Philosopher %d is alive\n", philos[i].id);
		i++;
	}
	return (1);
}

int	check_philos(t_philo *philos)
{
	int i;

	i = 0;
	while(i < philos->nb_philos)
	{
		if (!time_checker(&philos[i]))
		{
			print_thread(&philos[i], philos[i].id, PHILO_DIE);
			pthread_mutex_lock(philos->dead);
			*philos[i].dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			return (0);
		}
		i++;
		usleep(100);
	}
	return (1);
}

void	monitor(void *philos_in)
{
	t_philo *philos;

	philos = (t_philo *)philos_in;
	while(1)
	{
		if (!check_philos(philos) || !everyone_ate(philos))
		{
			return ;
		}
		usleep(100);
	}
	return ;
}
