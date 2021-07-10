/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/10 18:42:13 by avogt            ###   ########.fr       */
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

int	add_to_philosphers(t_philosophers *p, int index, t_constraints *cons)
{
	t_philo	*new;
	t_philo	*tmp;

	tmp = p->first;
	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (0);
	new->id = index;
	new->constraints = cons;
	new->next = NULL;
	if (p->first == NULL)
		p->first = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_philosophers	*initalize_philosophers(int nb, t_constraints *cons)
{
	t_philosophers	*philosophers;
	int				c;

	c = 0;
	philosophers = NULL;
	philosophers = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (philosophers == NULL)
		return (NULL);
	philosophers->first = NULL;
	while (c < nb)
	{
		if (!add_to_philosphers(philosophers, c + 1, cons))
		{
			//free_philosophers(philosophers);
			return (NULL);
		}
		c++;
	}
	return (philosophers);
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
	int				forks[199];
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
	cons->table.start = get_ms_time();
	philosophers = initalize_philosophers(cons->table.num_philosophers, cons);
	if (!philosophers)
		ft_error(NULL);
	counter = 0;
	while (counter < cons->table.num_philosophers)
	{
		philo = get_philo(philosophers, counter + 1);
		pthread_create(&philo->thread, NULL, eating, (void *)philo);
		counter++;
		forks[counter - 1] = 0;
	}
	counter = 0;
	while (counter < cons->table.num_philosophers)
	{
		philo = get_philo(philosophers, counter + 1);
		pthread_join(philo->thread, NULL);
		counter++;
	}
	ft_free_constraints(cons);
	return (0);
}
