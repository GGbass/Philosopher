/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:38:44 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 22:51:16 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static int	everyone_ate(t_data *data)
{
	sem_wait(data->dead);
	if (data->nb_philos == *data->philos->finished)
	{
		sem_wait(data->print);
		//data->dead_flag = 1;
		sem_post(data->dead);
		return (1);
	}
	sem_post(data->dead);
	return (0);
}

static int	time_checker(t_data *data)
{
	sem_wait(data->meal);
	if (get_time() - data->last_meal > data->time_to_die)
	{
		print_action(data, data->philos->id, PHILO_DIE);
		sem_wait(data->print);
		data->dead_flag = 1;
		data->philos->post_out = data->philos->id;
		sem_post(data->meal);
		return (0);
	}
	sem_post(data->meal);
	return (1);
}

void	*monitor(void	*dat)
{
	t_data *data;

	data = (t_data *)dat;
	while (1)
	{
		if (data->times_each_must_eat == 0)
			break ;
		if (!time_checker(data) || everyone_ate(data))
			break ;
		if (!alive_status(data))
			break ;
		usleep(10);
	}
	return (NULL);
}
