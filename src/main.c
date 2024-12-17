/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 14:21:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	thread_values(t_data *data)
{
	int	i;

	i = 0;
	data->forks = ft_calloc(data->philos->nb_philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		(perror("Error creating forks"), free_data(data));
	while (i < data->nb_philos && !(pthread_mutex_init(&data->forks[i], NULL)))
	{
		data->philos[i].id = i;
		data->philos[i].start_time = (int )get_time();
		data->philos[i].time_to_eat = data->philos->time_to_eat;
		data->philos[i].time_to_sleep = data->philos->time_to_sleep;
		data->philos[i].time_to_die = data->philos->time_to_die;
		data->philos[i].nb_philos = data->nb_philos;
		data->philos[i].times_each_must_eat = data->philos->times_each_must_eat;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].dead_flag = &data->dead_flag;
		if (i + 1 == data->philos->nb_philos)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

void	thread_init(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	data->time = get_time();
	thread_values(data);
	i = 0;
	while (i < philos->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, (void *)routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < philos->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

t_data	*init_values(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		free_data(data);
	data->philos = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!data->philos)
		free_data(data);
	data->nb_philos = ft_atoi(argv[1]);
	data->philos->time_to_die = ft_atoi(argv[2]);
	data->philos->time_to_eat = ft_atoi(argv[3]);
	data->philos->time_to_sleep = ft_atoi(argv[4]);
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
