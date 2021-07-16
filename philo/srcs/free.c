/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:22:34 by avogt             #+#    #+#             */
/*   Updated: 2021/07/16 11:11:51 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free_constraints(t_constraints *cons)
{
	free(cons);
	cons = NULL;
}

void	free_philosophers(t_philosophers *p)
{
	t_philo *ph;

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
	t_fork *fo;

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
