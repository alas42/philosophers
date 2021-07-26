/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 18:22:16 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*finish(t_philo *philo, int index)
{
	printing(&philo[index], DEAD);
	return (NULL);
}

void	*reaping(void *ptr)
{
	t_philo			*philos;
	int				counter;
	int				max_meal;
	int				i;

	philos = (t_philo *)ptr;
	max_meal = philos->infos->num_philos;
	counter = 0;
	while (counter != max_meal)
	{
		counter = 0;
		usleep(500);
		i = 0;
		while (i < max_meal)
		{
			if (philos[i].state != FULL
				&& get_ms_time() - philos[i].time >= philos[i].infos->time_to_die)
				return (finish(philos, i));
			else if (philos[i].state == FULL)
				counter++;
			i++;
		}
	}
	return (NULL);
}

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
	usleep(1000);
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
	pthread_t			grim_reaper;
	pthread_mutex_t		*forks;
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
	philos = init_philos(infos->num_philos, infos, forks);
	if (!philos)
		return (ft_error(infos, forks, NULL));
	pthread_create(&grim_reaper, NULL, reaping, (void *)philos);
	launch_forks(philos, infos);
	pthread_join(grim_reaper, NULL);
	wait_forks(philos, infos);
	ft_free(infos, forks, philos);
	return (0);
}
