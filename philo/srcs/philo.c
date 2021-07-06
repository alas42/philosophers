/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/06 11:22:23 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_philo	philo[200];
	int		forks[199];
	int counter;
	struct timeval start_tv;
	t_constraints *cons;

	if (argc == 0 || argv[0] == NULL)
		ft_usage();
	counter = 0;
	cons = (t_constraints *)malloc(sizeof(t_constraints));
	if (cons == NULL)
		ft_error();
	if (init(argc, argv, cons) == -1)
		ft_usage();
	gettimeofday(&start_tv, NULL);
	while (counter < cons->table.num_philosophers)
	{
		philo[counter].id = counter + 1;
		pthread_create(&philo[counter].thread, NULL, eating, (void *)&(philo[counter].id));
		counter++;
		forks[counter - 1] = 0;
	}
	counter = 0;
	while (counter < cons->table.num_philosophers)
	{
		usleep(1000);
		pthread_join(philo[counter].thread, NULL);
		counter++;
	}
	ft_free_constraints(cons);
	return (0);
}
