/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/27 18:57:53 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	launch_forks(t_philo *philos, t_infos *infos)
{
	int		i;

	i = 0;
	infos->start = get_ms_time();
	while (i < infos->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, dining, (void *)&philos[i]);
		i += 2;
	}
	i = 1;
	while (i < infos->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, dining, (void *)&philos[i]);
		i += 2;
	}
}

void	wait_forks(t_philo *philos, t_infos *infos)
{
	int		i;

	i = 0;
	while (i < infos->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
	t_infos				*infos;

	if (argc == 0 || argv[0] == NULL)
		ft_usage(NULL, NULL, NULL);
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (infos == NULL)
		return (ft_error(NULL, NULL, NULL));
	if (init(argc, argv, infos) == -1)
		return (ft_usage(infos, NULL, NULL));
	forks = init_forks(infos->num_philos);
	if (!forks)
		return (ft_error(infos, NULL, NULL));
	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, NULL);
	philos = init_philos(infos->num_philos, infos, forks, print);
	if (!philos)
		return (ft_error(infos, forks, NULL));
	launch_forks(philos, infos);
	wait_forks(philos, infos);
	pthread_mutex_destroy(print);
	free(print);
	ft_free(infos, forks, philos);
	return (0);
}
