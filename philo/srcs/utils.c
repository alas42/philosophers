/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 21:59:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/28 17:31:56 by avogt            ###   ########.fr       */
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

long long	get_ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	ft_usleep(long long time, long long desired_time, t_philo *p)
{
	long long	t;

	t = time;
	while (t - time < desired_time)
	{
		if (t - p->time < p->infos->time_to_die)
			usleep(100);
		else
			return (1);
		t = get_ms_time();
	}
	return (0);
}
