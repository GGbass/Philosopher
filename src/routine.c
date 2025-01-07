/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/07 21:42:16 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	sleeping(t_philo *philos)
{
	print_thread(philos, philos->id, PHILO_SLEEP);
	printf("time to sleep + current %d >= %d \n", philos->time_to_sleep + (int)get_time(), philos->time_to_die);
	if (philos->time_to_sleep + (int)get_time() >= philos->time_to_die)
	{
		ft_usleep(philos->time_to_die - (int)get_time());
	}
	else
		ft_usleep(philos->time_to_sleep);
}

void	take_forks(t_philo *philos)
{
	if (philos->id % 2 == 0 && philos->nb_philos % 2)
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
	//if (philos->id == philos->nb_philos - 1)
	if (philos->id % 2 == 0  && philos->nb_philos % 2)
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
}

int	check_philo(t_philo *philos)
{
	if (philos->times_each_must_eat == 0 || *philos->dead_flag == 1)
		return (0);
	if ((int )get_time() >= philos->time_to_die)
	{
		*philos->dead_flag = 1;
		print_thread(philos, philos->id, PHILO_DIE);
		return (0);
	}
	if (*philos->dead_flag == 1)
		return (0);
	return (1);
}

int	eating(t_philo *philos)
{
	take_forks(philos);
	if (!check_philo(philos))
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		return (0);
	}
	print_thread(philos, philos->id, PHILO_EAT);
	philos->last_meal = (int )get_time();
	philos->time_to_die = philos->last_meal + philos->ms_to_die;
	printf("Time to die: %d\n", philos->time_to_die);
	if (philos->time_to_eat + (int)get_time() >= philos->time_to_die)
		ft_usleep(philos->time_to_die - (int)get_time());
	else
		ft_usleep(philos->time_to_eat);//
	release_forks(philos);
	if (philos->times_each_must_eat != -1)
		philos->times_each_must_eat--;
	return (1);
}

void	*routine(t_philo *philos)
{
	philos->start_time = (int )get_time();
	philos->last_meal = philos->start_time;
	philos->ms_to_die = philos->time_to_die;
	philos->time_to_die = philos->last_meal + philos->ms_to_die;
	while (check_philo(philos) && !*philos->dead_flag)
	{
		if (philos->nb_philos == 1)
		{
			ft_usleep(philos->ms_to_die);
			print_thread(philos, philos->id, PHILO_DIE);
			return (NULL);
		}
		if (philos->id % 2 == 0)
			usleep(500); // 0,5 milisegundos 
		if (!eating(philos))
		{
			return (NULL);
		}
		if (check_philo(philos))
			sleeping(philos);
		if(check_philo(philos))
			think(philos);
		if (philos->times_each_must_eat == 0)
			return (NULL);
	}
	return (NULL);
}
