/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:14:21 by marvin            #+#    #+#             */
/*   Updated: 2025/02/06 01:14:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[++j])
		joined[i++] = s2[j];
	joined[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (joined);
}
void	print_action(t_data *data, int id, char *str)
{
	size_t	time;
// it has to be data
	/* if (!alive_status(philos))
		return ; */
	sem_wait(data->print);
	time = get_time() - data->time_start;
	printf("%ld %d %s\n", time, id, str);
	sem_post(data->print);
}
