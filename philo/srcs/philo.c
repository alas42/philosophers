/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/31 12:07:25 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_forks(t_philo *philos, t_infos *infos, pthread_mutex_t *print,
	pthread_mutex_t *forks)
{
	int		i;

	i = 0;
	while (i < infos->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(print);
	free(print);
	ft_free(infos, forks, philos);
}

void	launch_forks(t_philo *philos, t_infos *infos, pthread_mutex_t *print,
	pthread_mutex_t *forks)
{
	pthread_t	reaper;
	int			i;

	i = 0;
	pthread_mutex_init(print, NULL);
	infos->start = get_ms_time();
	while (i < infos->num_philos)
	{
		philos[i].time = infos->start;
		pthread_create(&philos[i].thread, NULL, dining, (void *)&philos[i]);
		i += 2;
	}
	i = 1;
	while (i < infos->num_philos)
	{
		philos[i].time = infos->start;
		pthread_create(&philos[i].thread, NULL, dining, (void *)&philos[i]);
		i += 2;
	}
	pthread_create(&reaper, NULL, reaping, philos);
	pthread_join(reaper, NULL);
	wait_forks(philos, infos, print, forks);
}

int	main(int argc, char *argv[])
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
	pthread_mutex_t		*infos_philos;
	t_infos				*infos;

	infos = (t_infos *)malloc(sizeof(t_infos));
	if (init(argc, argv, infos) == -1)
		return (ft_usage(infos, NULL, NULL));
	forks = init_forks(infos->num_philos);
	if (!forks)
		return (ft_error(infos, NULL, NULL));
	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!print)
		return (ft_error(infos, forks, NULL));
	infos_philos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* infos->num_philos);
	if (!infos_philos)
		return (ft_error(infos, forks, NULL));
	philos = init_philos(infos, forks, print, infos_philos);
	if (!philos)
		return (ft_error(infos, forks, NULL));
	launch_forks(philos, infos, print, forks);
	free(infos_philos);
	return (0);
}
