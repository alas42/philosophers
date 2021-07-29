/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:22:34 by avogt             #+#    #+#             */
/*   Updated: 2021/07/29 13:28:08 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(p[i].info_philo);
		i++;
	}
	free(p);
}

void	free_forks(pthread_mutex_t *f, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&f[i]);
		i++;
	}
	free(f);
}

void	ft_free(t_infos *i, pthread_mutex_t *f, t_philo *ps)
{
	int	n;

	n = i->num_philos;
	if (i)
	{
		free(i->str);
		free(i);
	}
	if (f)
		free_forks(f, n);
	if (ps)
		free_philos(ps, n);
}
