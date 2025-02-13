/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:38:44 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 20:21:55 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static int	everyone_ate(t_data *data)
{
	sem_wait(data->dead);
	if (data->nb_philos == *data->finished)
	{
		data->dead_flag = 1;
		*data->philos->dead_flag = 1;
		sem_post(data->dead);
		return (1);
	}
	sem_post(data->dead);
	return (0);
}

static int	time_checker(t_data *data)
{
	sem_wait(data->dead);
	if (get_time() - data->last_meal > data->time_to_die)
	{
		printf("rest time: %ld\n", get_time() - data->last_meal);
		printf("get time: %ld last meal %ld and time to die %ld\n", get_time(), data->last_meal, data->time_to_die);
		print_action(data, data->philos->id, PHILO_DIE);
		*data->philos->dead_flag = 1;
		sem_post(data->dead);
		//free_data(data);
		return (0);
	}
	sem_post(data->dead);
	return (1);
}

void	*monitor(void	*dat)
{
	t_data *data;

	data = (t_data *)dat;
	while (1)
	{
		if (!time_checker(data) || everyone_ate(data))
			break ;
		usleep(10);
	}
	return (NULL);
}
