/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:43:45 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/29 00:38:08 by marvin           ###   ########.fr       */
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

static int	everyone_ate(t_philo *philos)
{
	int i;
	int ate;

	i = 0;
	ate = 0;
	if (philos->times_each_must_eat == -1)
		return (1);
	while (i < philos->nb_philos)
	{
		printf("philo id %d times each must eat %d\n", philos[i].id, philos[i].times_each_must_eat);
		if (philos[i].times_each_must_eat == 0)
			ate++;
		if (ate == philos->nb_philos)
		{
			pthread_mutex_lock(philos->dead);
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			return (0);
		}
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
		pthread_mutex_lock(philos[i].dead);
		if (get_time() >= philos[i].time_to_die)
		{
			*philos[i].dead_flag = 1;
			print_thread(&philos[i], philos[i].id, PHILO_DIE);
			pthread_mutex_unlock(philos[i].dead);
			return (0);
		}
		pthread_mutex_unlock(philos[i].dead);
		usleep(100);
		i++;
	}
	return (1);
}

void	monitor(void *philos_in)
{
	t_philo *philos;

	philos = (t_philo *)philos_in;
	//printf("philos nb %d\n", philos->nb_philos);
	usleep(50);
	while(1)
	{
		if (philos->times_each_must_eat == 0 || *philos->dead_flag == 1)
		{
			pthread_mutex_lock(philos->dead);
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			break ;
		}
		if (!check_philos(philos) || !everyone_ate(philos))
		{
			break ;
		}
		usleep(100);
		//print_thread_values(philos);
	}
	return ;
}
