/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 20:07:22 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	waitier_routine(pthread_t waiter)
{
	printf("waiter routine\n");
}

void	routine(t_data *data)
{
	printf("here \n");
	//data->philos->time_to_eat += 300;
	printf("philo id %d\n", data->philos->id);
	printf("current time %ld\n", get_time());
	//printf("philo routine eating\n");
	//printf("philo routine sleeping\n");
	//printf("philo routine thinking\n");
}

void	thread_init(t_data *data)
{
	int			i;
	pthread_t	waiter;

	i = 0;
	data->start_time = get_time();
	pthread_mutex_lock(&data->philos->threads);
	while(i < data->philos->nb_philos)
	{
		printf("philo %d\n", i);
		pthread_create(&data->philos->threads[i], NULL, (void *)routine, NULL);
		i++;
	}
	pthread_create(&waiter, NULL, (void *)waiter_routine, NULL);
	i = 0;
	while(i < data->philos->nb_philos)
	{
		printf("time to eat %d\n", data->philos->time_to_eat);
		pthread_join(data->philos->threads[i], NULL);
		i++;
	}
	pthread_mutex_unlock(&data->philos->threads);
}

void	init_mutex(t_data *data)
{
	data->philos = ft_calloc(1, sizeof(t_philo));
	if (!data->philos)
		free_data(data);
	printf("init mutex\n");
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->sleep_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_argv(argc, argv))
		return (0);;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		free_data(data);
	init_mutex(data);
	data->philos->nb_philos = ft_atoi(argv[1]);
	thread_init(data);
	data->philos->threads = ft_calloc(data->philos->nb_philos, sizeof(pthread_t));
	if (!data->philos->threads) 
		return (free_data(data), 0);
	return (0);
}
