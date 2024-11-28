/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/27 01:30:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


/* void	waiter_routine(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->nb_philos)
	{
		pthread_mutex_lock(&philos->meal_mutex);
		if (philos[i].times_each_must_eat == 0)
			i++;
		pthread_mutex_unlock(&philos->meal_mutex);
	}
	pthread_mutex_lock(&philos->write_mutex);
	printf("All philos ate %d times\n", waiter->times_each_must_eat);
	pthread_mutex_unlock(&waiter->write_mutex);
} */

void	data_init(t_data *data)
{
	thread_values(data);
}

void	thread_init(t_data *data)
{
	int	i;

	data->time = get_time();
	pthread_mutex_lock(&data->start_philo);
	data_init(data);
	pthread_mutex_unlock(&data->start_philo);
	i = 0;
	while (i < data->philos->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, (void *)routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philos->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

t_data	*init_mutex(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		free_data(data);
	data->philos = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!data->philos)
		free_data(data);
	if (argc == 6)
		data->philos->times_each_must_eat = ft_atoi(argv[5]);
	else
		data->philos->times_each_must_eat = -1;
	pthread_mutex_init(&data->start_philo, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->sleep_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!check_argv(argc, argv))
		return (0);
	data = init_mutex(argc, argv);
	thread_init(data);
	free_data(data);
	return (0);
}
