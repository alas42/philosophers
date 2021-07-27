/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:29:51 by avogt             #+#    #+#             */
/*   Updated: 2021/07/27 13:29:34 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philos(int nb, t_infos *infos, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		c;

	c = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * nb);
	if (philos == NULL || forks == NULL)
		return (NULL);
	while (c < nb)
	{
		philos[c].infos = infos;
		philos[c].id = c + 1;
		philos[c].time = get_ms_time();
		philos[c].times_eating = 0;
		if (c == 0)
			philos[c].left_fork = &forks[nb - 1];
		else
			philos[c].left_fork = &forks[c - 1];
		if (nb != 1)
			philos[c].right_fork = &forks[c];
		else
			philos[c].right_fork = NULL;
		//pthread_mutex_init(&philos[c].mutex_time, NULL);
		c++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(int nb)
{
	pthread_mutex_t	*forks;
	int		c;

	c = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (forks == NULL)
		return (NULL);
	while (c < nb)
	{
		pthread_mutex_init(&forks[c], NULL);
		c++;
	}
	return (forks);
}
