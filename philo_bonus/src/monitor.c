/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:38:44 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 21:59:25 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

int	meals_check(t_data *data)
{
	if (data->times_each_must_eat > 0)
	{
		data->times_each_must_eat--;
		if (data->times_each_must_eat == 0)
		{
			ft_usleep(data->time_to_eat / 2);
			return (sem_post(data->start), 0);
		}
	}
	return (1);
}

int	alive_status(t_data *data)
{
	sem_wait(data->meal);
	if (*data->philos->dead_flag == 1)
	{
		sem_post(data->meal);
		return (0);
	}
	sem_post(data->meal);
	return (1);
}

static int	time_checker(t_data *data)
{
	sem_wait(data->meal);
	if (get_time() - data->last_meal > data->time_to_die)
	{
		print_action(data, data->philos->id, PHILO_DIE);
		sem_wait(data->print);
		*data->philos->dead_flag = 1;
		data->philos->post_out = data->philos->id;
		sem_post(data->meal);
		return (0);
	}
	sem_post(data->meal);
	return (1);
}

void	*monitor(void	*dat)
{
	t_data	*data;

	data = (t_data *)dat;
	while (1)
	{
		sem_wait(data->start);
		if (data->times_each_must_eat == 0)
		{
			sem_post(data->start);
			return (NULL);
			//break ;
		}
		sem_post(data->start);
		if (!time_checker(data))
			break ;
		if (!alive_status(data))
			break ;
		usleep(10);
	}
	exit(1);
}
