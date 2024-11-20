/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 19:21:03 by marvin           ###   ########.fr       */
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
		pthread_mutex_unlock(&philos->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philos->meal_mutex);
	return (1);
}

int	dead_philo(t_philo *philos)
{
	pthread_mutex_lock(&philos->dead_mutex);
	if (philos->dead_flag == 1)
	{
		pthread_mutex_unlock(&philos->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->dead_mutex);
	return (1);
}

int	check_philos(t_philo *philos)
{
	if (philos->times_each_must_eat == 0)
		return (0);
	pthread_mutex_lock(&philos->dead_mutex);
	if (philos->dead_flag == 1)
	{
		pthread_mutex_unlock(&philos->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->dead_mutex);
	return (0);
}

void	*routine(t_philo *philos)
{
	int i = 0;
//	pthread_mutex_lock(&philos->philo_begin);
//	pthread_mutex_unlock(&philos->philo_begin);
	/* if (philos->id % 2 == 0)
		ft_usleep(100); */
	//while (!waiter_routine(philos))
	while(i < philos->nb_philos)
	{
		print_thread(philos, philos[i].id, "is thinking");
		printf(" philo %d \n",philos[1].id);
		printf(" philo %d \n",philos[2].id);
		/* if (philos->id % 2 != 0)
			ft_usleep(100); */
		//if (!eating(philos))
		//	return (NULL);
		//if (philos->times_each_must_eat == 0)
		//	return (NULL);
		//sleeping(philos);
		//thinking(philos);
		i++;
		if (i == philos->nb_philos)
			i = 0;
	}
	return (philos);
}
