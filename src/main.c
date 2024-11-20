/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/20 21:04:47 by gongarci         ###   ########.fr       */
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

void	forks_init(t_data *data)
{
	int i;

	i = 0;
	thread_values(data);
	data->philos->start_time = get_time();
	data->philos->forks = ft_calloc(data->philos->nb_philos, sizeof(pthread_mutex_t));
	if (!data->philos->forks)
		(perror("Error creating forks"), free_data(data));
	while(i < data->philos->nb_philos)
	{
		pthread_mutex_init(&data->philos->forks[i], NULL);
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
	//pthread_create(&data->philos->waiter, NULL, (void *)waiter_routine, &data->philos->waiter);
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

	if (!check_argv(argc, argv))
		return (0);
	data = init_mutex(argc, argv);
	thread_init(data);
	free_data(data);
	return (0);
}
