/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:48:58 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:48:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free_data(t_data *data)
{
	if (data->philos)
	{
		free(data->philos->threads);
		//free(data->philos->forks);
		//free(data->philos->forks_status);
		//free(data->philos->forks_time);
		free(data->philos);
	}
	free(data);
}
