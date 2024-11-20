/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/20 22:59:24 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


int	eating(t_philo *philos)
{
	//check for fork taken;
	//print_philo_action();
	if (philos->nb_philos == 1)
	{
		ft_usleep(philos->time_to_die);
		return (0);
	}
	else if (philos->id % 2 != 0)
	{
		ft_usleep(100);
		pthread_mutex_lock(&philos->left_fork);
	}
	else
		pthread_mutex_lock(&philos->right_fork);
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
	/* if (philos->id % 2 == 0)
		ft_usleep(100); */
	//while (!waiter_routine(philos))
	pthread_mutex_lock(&philos->philo_begin);
	pthread_mutex_unlock(&philos->philo_begin);
	while(check_philos(philos))
	{
		/* if (philos->id % 2 != 0)
			ft_usleep(100); */
		if (!eating(philos))
		{
			printf("philo %d died\n", philos->id);
			return (NULL);
		}
		//if (philos->times_each_must_eat == 0)
		//	return (NULL);
		//sleeping(philos);
		//thinking(philos);
	}
	return (philos);
}
