/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:21:18 by avogt             #+#    #+#             */
/*   Updated: 2021/07/16 11:24:16 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_table(int ac, char *av[], t_constraints *c)
{
	c->table.num_philosophers = get_num_philosophers(av[1]);
	if (c->table.num_philosophers == -1)
		return (-1);
	c->table.num_forks = c->table.num_philosophers;
	if (c->table.num_philosophers == 1)
		c->table.num_forks -= 1;
	if (c->table.num_philosophers <= 0)
		return (-1);
	return (1);
}

static int	init_constraints(int ac, char *av[], t_constraints *cons)
{
	if (av[2] != NULL)
		cons->time_to_die = (int)get_time(av[2]);
	else
		cons->time_to_die = 1000;
	if (av[3] != NULL)
		cons->time_to_eat = (int)get_time(av[3]);
	else
		cons->time_to_eat = 200;
	if (av[4] != NULL)
		cons->time_to_sleep = (int)get_time(av[4]);
	else
		cons->time_to_sleep = 100;
	if (ac == 6 && av[5] != NULL)
		cons->nb_meal = (int)get_time(av[5]);
	else
		cons->nb_meal = -2;
	if (cons->time_to_die == -1 || cons->time_to_eat == -1 || cons->time_to_sleep == -1 || cons->nb_meal == -1)
		return (-1);
	cons->finished = 0;
	pthread_mutex_init(&cons->lock, NULL);
	return (1);
}

int	init(int ac, char *av[], t_constraints *c)
{
	if (ac < 5 || ac > 6)
		return (-1);
	if (init_table(ac, av, c) == 1 && init_constraints(ac, av, c) == 1)
		return (1);
	return (-1);
}
