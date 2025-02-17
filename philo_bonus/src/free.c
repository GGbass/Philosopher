/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/17 22:56:46 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void	kill_proccesses(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (1)
	{
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
}
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
 
	if (data->times_each_must_eat != -1)
	{
		while(data->nb_philos != *data->philos->finished)
		{
			if (data->nb_philos == *data->philos->finished)
				break;
			usleep(100);
		}
	} 
	if (data->times_each_must_eat == 0)
	{
		free_proccess(data);
	}
	if (data->philos->pid > 0)
		kill_proccesses(data);
	if (data->philos)
	{
		free(data->philos);
	}
	free(data);
}
