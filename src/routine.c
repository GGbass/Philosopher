/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/14 23:57:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


int	check_philos(t_philo *philos)
{
	if (philos->times_each_must_eat == 0)
		return (0);
	return (1);
}

pthread_t	*routine(t_philo *philos)
{
	printf("here \n");
	printf("philo id %d\n", philos->id);
	printf("current time %ld\n", get_time());
	pthread_mutex_lock(&philos->start_philo);
	pthread_mutex_unlock(&philos->start_philo);
	while(check_philos(philos))
	{
		printf("philo %d is thinking\n", philos->id);
		printf("philo %d is eating\n", philos->id);
		printf("philo %d is sleeping\n", philos->id);
	}
}