/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 21:59:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/27 15:25:22 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	get_ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	ft_usleep(size_t time, size_t desired_time, t_philo *p)
{
	size_t	t;

	t = get_ms_time();
	while (t - time < desired_time)
	{
		if (t - p->time < p->infos->time_to_die)
		{
			usleep(100);
			t = get_ms_time();
		}
		else
		{
			return (1);
		}
	}
	return (0);
}
