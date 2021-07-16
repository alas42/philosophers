/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:29:51 by avogt             #+#    #+#             */
/*   Updated: 2021/07/16 11:23:11 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	add_to_philosophers(t_philosophers *p, int index, t_constraints *cons, t_forks *forks)
{
	t_philo	*new;
	t_philo	*tmp;

	tmp = p->first;
	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (0);
	new->id = index;
	new->constraints = cons;
	new->times_eating = 0;
	new->state = get_state_ptr();
	new->right_fork = get_fork_ptr(forks, index);
	new->next = NULL;
	if (p->first == NULL)
	{
		new->left_fork = get_fork_ptr(forks, cons->table.num_forks);
		p->first = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->left_fork = get_fork_ptr(forks, index - 1);
		tmp->next = new;
	}
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

t_philosophers	*initalize_philosophers(int nb, t_constraints *cons, t_forks *forks)
{
	t_philosophers	*philosophers;
	int				c;

	c = 0;
	philosophers = NULL;
	philosophers = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (philosophers == NULL || forks == NULL)
		return (NULL);
	philosophers->first = NULL;
	while (c < nb)
	{
		if (!add_to_philosophers(philosophers, c + 1, cons, forks))
		{
			free_philosophers(philosophers);
			return (NULL);
		}
		c++;
	}
	return (philosophers);
}

t_forks	*initialize_forks(int nb)
{
	t_forks *forks;
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
