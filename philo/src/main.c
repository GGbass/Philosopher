/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 10:17:20 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = ft_calloc(data->philos->nb_philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		(write(2, "Error creating forks", 20), free_data(data));
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->start, NULL);
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			(write(2, "Error creating forks", 20), free_data(data));
		i++;
	}
	mutex_assigner(data);
}

static void	thread_values(t_data *data)
{
	int		i;
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
	int			i;
	pthread_t	monitorer;
	t_philo		*p;

	i = 0;
	p = data->philos;
	thread_values(data);
	pthread_mutex_lock(&data->start);
	if (pthread_create(&monitorer, NULL, (void *)monitor, p) != 0)
		(write(2, "Error creating monitor thread", 20), free_data(data));
	while (i < p->nb_philos)
	{
		if (pthread_create(&p[i].thread, NULL, (void *)routine, &p[i]) != 0)
			(write(2, "Error creating threads", 20), free_data(data));
		i++;
	}
	pthread_mutex_unlock(&data->start);
	i = 0;
	if (pthread_join(monitorer, NULL) != 0)
		(write(2, "Error joining monitor thread", 20), free_data(data));
	while (i < p->nb_philos)
	{
		pthread_join(p[i].thread, NULL);
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

/* 	i = 0;
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
	} */