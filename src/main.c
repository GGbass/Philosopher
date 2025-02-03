/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 00:22:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	print_values(t_data *data)
{
	printf("nb_philos: %d\n", data->nb_philos);
	printf("time_to_eat: %zu\n", data->philos->time_to_eat);
	printf("time_to_sleep: %zu\n", data->philos->time_to_sleep);
	printf("times_each_must_eat: %d\n", data->philos->times_each_must_eat);
	printf("time to start: %zu\n", data->time);
	printf("time to die: %zu\n", data->philos->time_to_die);
	printf("current - start: %zu\n", get_time() - data->time);
	printf("time to eat: %zu\n", data->philos->time_to_eat);
	printf("time to sleep: %zu\n", data->philos->time_to_sleep);
	printf("ms to die: %zu\n", data->philos->ms_to_die);
}

static void	mutex_init(t_data *data)
{
	int i;

	i = 0;
	data->forks = ft_calloc(data->philos->nb_philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		(write(2, "Error creating forks", 20), free_data(data));
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->start, NULL);
	while(i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			(write(2, "Error creating forks", 20), free_data(data));
		i++;
	}
	i = 0;
	while(i < data->nb_philos)
	{
		data->philos[i].print = &data->print;
		data->philos[i].meal = &data->meal;
		data->philos[i].dead = &data->dead;
		data->philos[i].start = &data->start;
		data->philos[i].left_fork = &data->forks[i];
		if (i + 1 == data->philos->nb_philos)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

static void	thread_values(t_data *data)
{
	int	i;
	t_philo	*philo;

	philo = data->philos;
	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].time_to_eat = data->philos->time_to_eat;
		philo[i].time_to_sleep = data->philos->time_to_sleep;
		philo[i].time_to_die = data->philos->time_to_die;
		philo[i].nb_philos = data->nb_philos;
		philo[i].times_each_must_eat = data->philos->times_each_must_eat;
		philo[i].dead_flag = &data->dead_flag;
		philo[i].start_time = get_time();
		philo[i].last_meal = get_time();
		philo[i].ms_to_die = philo[i].time_to_die;
		philo[i].time_to_die = philo[i].last_meal + philo[i].ms_to_die;
		i++;
	}
	mutex_init(data);
}

static void	thread_init(t_data *data)
{
	int		i;
	pthread_t	monitorer;
	t_philo		*philos;

	i = 0;
	philos = data->philos;
	thread_values(data);
	//print_values(data);
	pthread_mutex_lock(&data->start);
	while (i < philos->nb_philos)
	{
		/* philos[i].start_time = get_time();
		philos[i].last_meal = get_time();
		philos[i].time_to_die = philos[i].last_meal + philos[i].ms_to_die; */
		if (pthread_create(&philos[i].thread, NULL, (void *)routine, &philos[i]) != 0)
			(write(2, "Error creating threads", 20), free_data(data));
		i++;
	}
	if (pthread_create(&monitorer, NULL, (void *)monitor, philos) != 0)
		(write(2, "Error creating monitor thread", 20), free_data(data));
	pthread_mutex_unlock(&data->start);
	i = 0;
	if (pthread_join(monitorer, NULL) != 0)
		(write(2, "Error joining monitor thread", 20), free_data(data));
	while (i < philos->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

static t_data	*init_values(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		free_data(data);
	data->philos = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!data->philos)
		free_data(data);
	data->nb_philos = ft_atoi(argv[1]);
	data->philos->time_to_die = (long)ft_atoi(argv[2]);
	data->philos->time_to_eat = (long)ft_atoi(argv[3]);
	data->philos->time_to_sleep = (long)ft_atoi(argv[4]);
	if (argc == 6)
		data->philos->times_each_must_eat = ft_atoi(argv[5]);
	else
		data->philos->times_each_must_eat = -1;
	data->dead_flag = 0;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!check_argv(argc, argv))
		return (0);
	data = init_values(argc, argv);
	thread_init(data);
	free_data(data);
	return (0);
}
