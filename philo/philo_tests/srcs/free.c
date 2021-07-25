/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:22:34 by avogt             #+#    #+#             */
/*   Updated: 2021/07/18 13:49:47 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_infos(t_infos *infos)
{
	free(infos);
	infos = NULL;
}

void	free_philos(t_philos *p)
{
	t_philo	*ph;

	ph = NULL;
	while (p->first)
	{
		ph = p->first;
		p->first = p->first->next;
		pthread_mutex_destroy(&ph->state->lock);
		free(ph->state);
		free(ph);
	}
	free(p);
}

void	free_forks(t_forks *f)
{
	t_fork	*fo;

	fo = NULL;
	while (f->first)
	{
		fo = f->first;
		f->first = f->first->next;
		pthread_mutex_destroy(&fo->lock);
		free(fo);
	}
	free(f);
}

void	ft_free(t_infos *i, t_forks *f, t_philos *ps)
{
	if (i)
		free_infos(i);
	if (f)
		free_forks(f);
	if (ps)
		free_philos(ps);
}
