/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:21:18 by avogt             #+#    #+#             */
/*   Updated: 2021/07/24 10:53:17 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_table(int ac, char *av[], t_infos *c)
{
	c->table.num_philosophers = get_num_philosophers(av[1]);
	if (c->table.num_philosophers == -1)
		return (-1);
	c->table.num_forks = c->table.num_philosophers;
	if (c->table.num_philosophers <= 0)
		return (-1);
	return (1);
}

static int	init_constraints(int ac, char *av[], t_infos *infos)
{
	if (av[2] != NULL)
		infos->time_to_die = (uint64_t)get_time(av[2]);
	else
		infos->time_to_die = -1;
	if (av[3] != NULL)
		infos->time_to_eat = (uint64_t)get_time(av[3]);
	else
		infos->time_to_eat = -1;
	if (av[4] != NULL)
		infos->time_to_sleep = (uint64_t)get_time(av[4]);
	else
		infos->time_to_sleep = -1;
	if (ac == 6 && av[5] != NULL)
		infos->nb_meal = (uint64_t)get_time(av[5]);
	else
		infos->nb_meal = -2;
	if (infos->time_to_die == -1 || infos->time_to_eat == -1
		|| infos->time_to_sleep == -1 || infos->nb_meal == -1)
		return (-1);
	infos->finished = 0;
	pthread_mutex_init(&infos->lock, NULL);
	return (1);
}

int	init(int ac, char *av[], t_infos *c)
{
	if (ac < 5 || ac > 6)
		return (-1);
	if (init_table(ac, av, c) == 1 && init_constraints(ac, av, c) == 1)
		return (1);
	return (-1);
}
