/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:48:58 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 15:36:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			data->philos[i].left_fork = NULL;
			data->philos[i].right_fork = NULL;
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	free(data);
	exit(0);
}
