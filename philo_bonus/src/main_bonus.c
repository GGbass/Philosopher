/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:53:01 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/08 00:27:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static void	sem_assigner(t_data *data)
{
	char	*id;
	char	*aux;

	aux = malloc(2);
	if (!aux)
		(write(2, "Error creating aux in join", 26), free_data(data));
	aux[0] = data->philos->	id + '0';
	aux[1] = '\0';
	id = ft_strjoin("/", aux);
	if (!id)
		(write(2, "Error creating id in join", 25), free_data(data));
	sem_unlink(id);
	data->meal = sem_open(id, O_CREAT, 0644, 1);
	if (id)
		free(id);
	if (data->meal == SEM_FAILED)
		(write(2, "Error creating meal semaphore", 29), free_data(data));
}

static void	process_maker(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->nb_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			data->philos[i].id = i + 1;
			sem_assigner(data);
			//philo_routine(&data->philos[i]);
			//free_process();
		}
		else if (data->philos[i].pid < 0)
			(write(2, "Error creating process", 23), free_data(data));
		i++;
	}
}

static void	sema_init(t_data *data)
{
	sem_unlink("/print");
	sem_unlink("/meal");
	sem_unlink("/dead");
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philos);
	if (data->forks == SEM_FAILED)
		(write(2, "Error creating forks", 20), free_data(data));
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		(write(2, "Error creating print", 20), free_data(data));
	data->meal = sem_open("/meal", O_CREAT, 0644, 1);
	if (data->meal == SEM_FAILED)
		(write(2, "Error creating meal", 19), free_data(data));
	data->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if (data->dead == SEM_FAILED)
		(write(2, "Error creating dead", 19), free_data(data));
	
}

static t_data	*init_argv(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		(free_data(data), write(2, "Error creating data", 20));
	data->philos = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!data->philos)
		(free_data(data), write(2, "Error creating philos", 21));
	data->philos->id = 0;
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = (long)ft_atoi(argv[2]);
	data->time_to_eat = (long)ft_atoi(argv[3]);
	data->time_to_sleep = (long)ft_atoi(argv[4]);
	data->philos->dead_flag = &data->dead_flag;
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
	data = init_argv(argc, argv);
	sema_init(data);
	process_maker(data);
	free_data(data);
	return (0);
}
