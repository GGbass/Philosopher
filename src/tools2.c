/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:24:21 by marvin            #+#    #+#             */
/*   Updated: 2024/11/27 01:32:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	print_thread(t_philo *philos, int id, char *str)
{
	size_t	time;

	time = get_time() - philos->start_time;
	printf("%ld %d %s\n", time, id, str);
}

/* void	philo_and_fork_assigner(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while(i < data->philos->nb_philos)
	{
		data->philos->threads[i] = i;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
} */

void	thread_values(t_data *data)
{
	int i;
	pthread_mutex_t	*forks;

	i = 0;
	//philo_and_fork_assigner(data);
	forks = ft_calloc(data->philos->nb_philos, sizeof(pthread_mutex_t));
	if (!forks)
		(perror("Error creating forks"), free_data(data));
	while(i < data->philos->nb_philos && pthread_mutex_init(&forks[i], NULL))
	{
		//pthread_mutex_init(&forks[i], NULL);
		//data->philos->thread[i] = i;
		data->philos[i].id = i;
		data->philos[i].start_time = (int )get_time();
		data->philos[i].time_to_eat = data->philos->time_to_eat;
		data->philos[i].time_to_sleep = data->philos->time_to_sleep;
		data->philos[i].time_to_die = data->philos->time_to_die;
		data->philos[i].nb_philos = data->philos->nb_philos;
		data->philos[i].times_each_must_eat = data->philos->times_each_must_eat;
		data->philos[i].left_fork = &forks[i + 1];
		data->philos[i].right_fork = &forks[data->philos->nb_philos - 1];
		i++;
	}
}
