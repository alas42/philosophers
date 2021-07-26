/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:21:18 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 15:12:48 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_table(int ac, char *av[], t_infos *c)
{
	if (ac < 2)
		return (-1);
	c->num_philos = get_num_philosophers(av[1]);
	if (c->num_philos == 0)
		return (-1);
	return (1);
}

static int	init_constraints(int ac, char *av[], t_infos *infos)
{
	int check[3];
	
	if (av[2] != NULL)
		check[0] = get_time(av[2]);
	else
		return (-1);
	if (av[3] != NULL)
		check[1] = get_time(av[3]);
	else
		return (-1);
	if (av[4] != NULL)
		check[2] = get_time(av[4]);
	else
		return (-1);
	if (ac == 6 && av[5] != NULL)
		infos->nb_meal = get_time(av[5]);
	else
		infos->nb_meal = -2;
	if (check[0] <= 0 || check[1] == -1
		|| check[2] == -1 || infos->nb_meal == 0 || infos->nb_meal == -1)
		return (-1);
	infos->time_to_die = check[0];
	infos->time_to_eat = check[1];
	infos->time_to_sleep = check[2];
	infos->finished = 0;
	pthread_mutex_init(&infos->print, NULL);
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
