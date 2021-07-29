/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/29 13:35:56 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->info_philo);
	if (get_ms_time() - philo->time >= philo->infos->time_to_die)
	{
		pthread_mutex_unlock(philo->info_philo);
		printing(philo, DEAD, get_ms_time());
		return (1);
	}
	return (0);
}

void	*reaping(void *ptr)
{
	t_philo		*philos;
	int			i;
	int			counter;

	counter = 0;
	philos = (t_philo *)ptr;
	while (counter < philos[0].infos->num_philos)
	{
		i = -1;
		counter = 0;
		usleep(500);
		while (++i < philos[0].infos->num_philos)
		{
			if (philos[i].times_eating == philos[i].infos->nb_meal)
				counter++;
			else if (check_philo(&philos[i]))
				return (NULL);
			pthread_mutex_unlock(philos[i].info_philo);
		}
	}
	return (NULL);
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

void	launch_forks(t_philo *philos, t_infos *infos, pthread_mutex_t *print)
{
	pthread_t	reaper;
	int			i;

	i = 0;
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
	wait_forks(philos, infos);
	pthread_mutex_destroy(print);
	free(print);
}

int	main(int argc, char *argv[])
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
	pthread_mutex_t		*infos_philos;
	t_infos				*infos;

	if (argc == 0 || argv[0] == NULL)
		ft_usage(NULL, NULL, NULL);
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (init(argc, argv, infos) == -1)
		return (ft_usage(infos, NULL, NULL));
	forks = init_forks(infos->num_philos);
	if (!forks)
		return (ft_error(infos, NULL, NULL));
	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	infos_philos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* infos->num_philos);
	pthread_mutex_init(print, NULL);
	philos = init_philos(infos, forks, print, infos_philos);
	if (!philos)
		return (ft_error(infos, forks, NULL));
	launch_forks(philos, infos, print);
	ft_free(infos, forks, philos);
	free(infos_philos);
	return (0);
}
