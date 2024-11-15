/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/15 18:13:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	waiter_routine(t_data *data)
{
	printf("waiter routine\n");
	printf("waiter nb, %ld\n ", data->philos->waiter);
}

void	forks_init(t_data *data)
{
	int i;

	i = 0;
	data->philos->forks = ft_calloc(data->philos->nb_philos, sizeof(pthread_mutext_t));
	if (!data->philos->forks)
		(perror("Error creating forks"), free_data(data));
	while(i < data->philos->nb_philos)
	{
		pthread_mutex_init(data->philos->forks[i], NULL);
		i++;
	}
	printf("out of forks init while \n");
}

void	thread_init(t_data *data)
{
	int	i;

	i = 0;
	data->time = get_time();
	pthread_mutex_lock(&data->start_philo);
	data->philos->threads = ft_calloc(data->philos->nb_philos, sizeof(pthread_t));
	if (!data->philos->threads)
		free_data(data);
	while (i < data->philos->nb_philos)
	{
		printf("philo %d\n", i);
		pthread_create(&data->philos->threads[i], NULL, (void *)routine, &data->philos[i]);
		i++;
	}
	forks_init(data);
	pthread_create(&data->philos->waiter, NULL, (void *)waiter_routine, &data->waiter);
	
	i = 0;
	while (i < data->philos->nb_philos)
	{
		pthread_join(data->philos->threads[i], NULL);
		i++;
	}
	pthread_mutex_unlock(&data->start_philo);
}

t_data	*init_mutex(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		free_data(data);
	data->philos = ft_calloc(1, sizeof(t_philo));
	if (!data->philos)
		free_data(data);
	data->philos->forks = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_mutex_t));
	if (!data->philos->forks)
		free_data(data);
	data->philos->nb_philos = ft_atoi(argv[1]);
	data->philos->time_to_die = ft_atoi(argv[2]);
	data->philos->time_to_eat = ft_atoi(argv[3]);
	data->philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->philos->times_each_must_eat = ft_atoi(argv[5]);
	else
		data->philos->nb_times_each_philo_must_eat = -1;
	pthread_mutex_init(&data->philos->start_philo, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->sleep_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_argv(argc, argv))
		return (0);
	data = init_mutex(argc, argv);
	thread_init(data);
	data->philos->threads = ft_calloc(data->philos->nb_philos, sizeof(pthread_t));
	if (!data->philos->threads) 
		return (free_data(data), 0);
	return (0);
}
