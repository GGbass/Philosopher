/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/11 15:24:24 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void	free_data(t_data *data)
{
	free(data->philos);
	free(data);
	exit(1);
}
