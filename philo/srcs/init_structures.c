/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:29:51 by avogt             #+#    #+#             */
/*   Updated: 2021/07/29 13:33:36 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philos(t_infos *infos, pthread_mutex_t *forks,
			pthread_mutex_t *print, pthread_mutex_t *i_p)
{
	t_philo	*philos;
	int		c;

	c = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * infos->num_philos);
	if (philos == NULL || forks == NULL)
		return (NULL);
	while (++c < infos->num_philos)
	{
		philos[c].infos = infos;
		philos[c].id = c + 1;
		philos[c].times_eating = 0;
		if (c == 0)
			philos[c].left_fork = &forks[infos->num_philos - 1];
		else
			philos[c].left_fork = &forks[c - 1];
		if (infos->num_philos != 1)
			philos[c].right_fork = &forks[c];
		else
			philos[c].right_fork = NULL;
		philos[c].print = print;
		pthread_mutex_init(&i_p[c], NULL);
		philos[c].info_philo = &i_p[c];
	}
	return (philos);
}

pthread_mutex_t	*init_forks(int nb)
{
	pthread_mutex_t	*forks;
	int				c;

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
