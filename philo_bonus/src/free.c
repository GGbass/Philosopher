/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/12 22:03:01 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void	kill_proccesses(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	free_data(t_data *data)
{

	free(data->philos);
	free(data);
}
