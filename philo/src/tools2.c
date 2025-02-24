/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:24:21 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 07:35:42 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	mutex_assigner(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philos;
	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].print = &data->print;
		philo[i].meal = &data->meal;
		philo[i].dead = &data->dead;
		philo[i].start = &data->start;
		philo[i].left_fork = &data->forks[i];
		if (i + 1 == data->philos->nb_philos)
			philo[i].right_fork = &data->forks[0];
		else
			philo[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

void	print_thread(t_philo *philos, int id, char *str)
{
	size_t	time;

	if (!alive_status(philos))
		return ;
	pthread_mutex_lock(philos->print);
	time = get_time() - philos->start_time;
	printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(philos->print);
}

int	think(t_philo *philos)
{
	if (!alive_status(philos))
		return (0);
	print_thread(philos, philos->id, PHILO_THINK);
	return (1);
}

int	alive_status(t_philo *philos)
{
	pthread_mutex_lock(philos->dead);
	if (*philos->dead_flag == 1)
	{
		pthread_mutex_unlock(philos->dead);
		return (0);
	}
	pthread_mutex_unlock(philos->dead);
	return (1);
}
