/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:14:21 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 00:27:24 by marvin           ###   ########.fr       */
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
	j = -1;
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
	if (s2)
		free(s2);
	return (joined);
}
void	print_action(t_data *data, int id, char *str)
{
	size_t	time;

	/* if (!check_alive(data))
		return ; */
	sem_wait(data->print);
	time = get_time() - data->time_start;
	printf("%ld %d %s\n", time, id, str);
	sem_post(data->print);
	return ;
}

char	*ft_itoa(int num)
{
	int		len;
	int		tmp;
	char	*str;

	len = 1;
	tmp = num;
	if (num < 0)
	{
		len++;
		tmp *= -1;
	}
	while (tmp /= 10)
		len++;
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	if (num < 0)
		str[0] = '-';
	str[len] = '\0';
	while (len--)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
