/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/19 00:25:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

/* void	kill_proccesses(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	//while (waitpid(-1, &status, 0) > 0)
	while (1)
	{
		printf("waiting??\n");
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			while(i < data->nb_philos)
			{
				kill(data->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
	}
	WIFEXITED(status);
} */
void	free_proccess(t_data *data)
{
	kill(data->philos->pid, SIGKILL);
	if (data->philos)
		free(data->philos);
	free(data);
	exit(0);
}

void	free_data(t_data *data)
{
 
/* 	if (data->times_each_must_eat != -1)
	{
		while(data->nb_philos != *data->philos->finished)
		{
			usleep(100);
		}
	} */
	if (data->times_each_must_eat == 0)
	{
		free_proccess(data);
	}
	//kill_proccesses(data);
	if (data->philos)
	{
		free(data->philos);
	}
	free(data);
}
