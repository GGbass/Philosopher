/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:43:45 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/03 11:37:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/* static void	print_threads_values(t_philo *philos)
{
	int i;

	i = -1;
	while (++i < philos->nb_philos)
	{
		pthread_mutex_lock(philos[i].print);
		printf("address: %p\n", &philos[i]);
		printf("id: %d\n", philos[i].id);
		printf("time_to_eat: %zu\n", philos[i].time_to_eat);
		printf("time_to_sleep: %zu\n", philos[i].time_to_sleep);
		printf("time_to_die: %zu\n", philos[i].time_to_die);
		printf("ms_to_die: %zu\n", philos[i].ms_to_die);
		printf("start_time: %zu\n", philos[i].start_time);
		printf("last_meal: %zu\n", philos[i].last_meal);
		printf("nb_philos: %d\n", philos[i].nb_philos);
		printf("times_each_must_eat: %d\n", philos->times_each_must_eat);
		printf("dead_flag: %d\n", *philos[i].dead_flag);
		pthread_mutex_unlock(philos->print);
	}
} */

static int	time_checker(t_philo *philos)
{
	pthread_mutex_lock(philos->meal);
	if (get_time() > philos->time_to_die)
	{
		pthread_mutex_unlock(philos->meal);
		return (0);
	}
	pthread_mutex_unlock(philos->meal);
	return (1);
}

static int	everyone_ate(t_philo *philos)
{
	int i;
	int ate;

	i = 0;
	ate = 0;
	pthread_mutex_lock(philos->meal);
	if (philos->times_each_must_eat == -1 || !alive_status(philos))
	{
		pthread_mutex_unlock(philos->meal);
		return (1);
	}
	pthread_mutex_unlock(philos->meal);
	while (i < philos->nb_philos)
	{
		pthread_mutex_lock(philos->meal);
		pthread_mutex_lock(philos->dead);
		if (philos[i].times_each_must_eat == 0)
			ate++;
		pthread_mutex_unlock(philos->meal);
		if (ate == philos->nb_philos)
		{
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			return (0);
		}
		pthread_mutex_unlock(philos->dead);
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
		//if (get_time - philos[i].last_meal > philos[i].time_to_die)
		if (!time_checker(&philos[i]))
		{
			pthread_mutex_lock(philos->dead);
			//pthread_mutex_lock(philos->print);
			//printf(" philo: %d get time %zu and time to die %zu\n", philos[i].id , get_time(), philos[i].time_to_die);
			//printf("result %zu\n", get_time() - philos[i].time_to_die);
			*philos[i].dead_flag = 1;
			//pthread_mutex_unlock(philos->print);
			print_thread(&philos[i], philos[i].id, PHILO_DIE);
			pthread_mutex_unlock(philos->dead);
			return (0);
		}
		i++;
		usleep(100);
		//pthread_mutex_unlock(philos->dead);
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
		//	printf("philos nb %d\n", philos->nb_philos);
			return ;
		}
		usleep(100);
	}
	return ;
}
