/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:43:45 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/27 23:26:45 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

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
			return (0);
		i++;
	}
	return (1);
}

int	check_philos(t_data *data)
{
	int i;
	t_philo *philos;

	philos = data->philos;
	i = 0;
	printf("inside check_philos%d\n", data->nb_philos);
	while(i < data->philos->nb_philos)
	{
		usleep(100);
		pthread_mutex_lock(philos[i].dead);
		if (get_time() >= philos[i].time_to_die && !*philos[i].dead_flag)
		{
			//*philos[i].dead_flag = 1;
			print_thread(&philos[i], philos[i].id, PHILO_DIE);
			pthread_mutex_unlock(philos[i].dead);
			return (0);
		}
		pthread_mutex_unlock(philos[i].dead);
		i++;
	}
	return (1);
}

void	*monitor(t_data *data)
{
	t_philo	*philos;

	data->dead_flag = 0;
	philos = data->philos;
	printf("inside monitor %d\n", data->nb_philos);
	while(1)
	{
		//printf("inside monitor %d\n");
		if (!check_philos(data) || !everyone_ate(philos))
		{
			pthread_mutex_lock(philos->dead);
			data->dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			//return (0);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
