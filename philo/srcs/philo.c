/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/12 14:25:34 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philosophers(t_philosophers *p)
{
	t_philo *ph;

	ph = NULL;
	while (p->first)
	{
		ph = p->first;
		p->first = p->first->next;
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
		free(fo);
	}
	free(f);
}

t_fork	*get_fork_ptr(t_forks *forks, int index)
{
	t_fork	*fork;

	fork = forks->first;
	while (fork->index != index)
		fork = fork->next;
	return (fork);
}

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
	new->time = 0;
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

t_philo	*get_philo(t_philosophers *p, int index)
{
	t_philo *philo;

	philo = p->first;
	while (philo != NULL)
	{
		if (philo->id == index)
			return (philo);
		philo = philo->next;
	}
	return (philo);
}

int	main(int argc, char *argv[])
{
	t_philosophers	*philosophers;
	t_philo			*philo;
	t_forks			*forks;
	int 			counter;
	t_constraints	*cons;

	if (argc == 0 || argv[0] == NULL)
		ft_usage(NULL);
	counter = 0;
	cons = (t_constraints *)malloc(sizeof(t_constraints));
	if (cons == NULL)
		ft_error(NULL);
	if (init(argc, argv, cons) == -1)
		ft_usage(cons);
	forks = initialize_forks(cons->table.num_forks);
	philosophers = initalize_philosophers(cons->table.num_philosophers, cons, forks);
	if (!forks || !philosophers)
		ft_error(NULL);
	counter = 0;
	cons->table.start = get_ms_time();
	while (counter < cons->table.num_philosophers)
	{
		philo = get_philo(philosophers, counter + 1);
		//printf("philo %d || left_fork_index : %d || right_fork_index : %d\n", philo->id, philo->left_fork->index, philo->right_fork->index);
		pthread_create(&philo->thread, NULL, dining, (void *)philo);
		counter++;
	}
	counter = 0;
	while (counter < cons->table.num_philosophers)
	{
		philo = get_philo(philosophers, counter + 1);
		pthread_join(philo->thread, NULL);
		counter++;
	}
	ft_free_constraints(cons);
	free_forks(forks);
	free_philosophers(philosophers);
	return (0);
}
