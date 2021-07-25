/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:29:51 by avogt             #+#    #+#             */
/*   Updated: 2021/07/25 17:05:58 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	add_to_philos(t_philos *p, int index, t_infos *infos, t_forks *forks)
{
	t_philo	*new;
	t_philo	*tmp;

	tmp = p->first;
	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (0);
	new->id = index;
	new->infos = infos;
	new->right_fork = get_fork_ptr(forks, index);
	new->state = get_state_ptr();
	new->next = NULL;
	if (p->first == NULL)
	{
		new->left_fork = get_fork_ptr(forks, infos->table.num_philos);
		p->first = new;
		return (1);
	}
	new->left_fork = get_fork_ptr(forks, index - 1);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	add_to_forks(t_forks *f, int index)
{
	t_fork	*new;
	t_fork	*tmp;

	tmp = f->first;
	new = malloc(sizeof(t_fork));
	if (new == NULL)
		return (0);
	new->index = index;
	pthread_mutex_init(&new->lock, NULL);
	new->taken = 0;
	new->next = NULL;
	if (f->first == NULL)
		f->first = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_philos	*init_philos(int nb, t_infos *infos, t_forks *forks)
{
	t_philos	*philos;
	t_philo		*philo;
	int			c;

	c = 0;
	philos = NULL;
	philos = (t_philos *)malloc(sizeof(t_philos));
	if (philos == NULL || forks == NULL)
		return (NULL);
	philos->first = NULL;
	while (c < nb)
	{
		if (!add_to_philos(philos, c + 1, infos, forks))
		{
			free_philos(philos);
			return (NULL);
		}
		philo = get_philo(philos, c + 1);
		if (nb == 1)
			philo->right_fork = NULL;
		c++;
	}
	return (philos);
}

t_forks	*init_forks(int nb)
{
	t_forks	*forks;
	int		c;

	c = 0;
	forks = (t_forks *)malloc(sizeof(t_forks));
	if (forks == NULL)
		return (NULL);
	forks->first = NULL;
	while (c < nb)
	{
		if (!add_to_forks(forks, c + 1))
		{
			free_forks(forks);
			return (NULL);
		}
		c++;
	}
	return (forks);
}
