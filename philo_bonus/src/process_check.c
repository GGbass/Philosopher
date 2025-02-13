/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:31:30 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/13 20:02:02 by gongarci         ###   ########.fr       */
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

int	alive_status(t_data *data)
{
	sem_wait(data->dead);
	if (*data->philos->dead_flag == 1 || data->dead_flag == 1)
	{
		sem_post(data->dead);
		return (0);
	}
	sem_post(data->dead);
	return (1);
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

int	check_alive(t_data *data)
{
		if (!time_checker(data) || !alive_status(data))
			return (0);
		if (everyone_ate(data))
			return (0);
		return (1);
}
