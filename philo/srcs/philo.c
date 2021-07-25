/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/24 17:12:08 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*finish(t_philo *philo)
{
	printing(philo, DEAD);
	pthread_mutex_unlock(&philo->state->lock);
	return (NULL);
}

void	*reaping(void *ptr)
{
	t_philo		*philo;
	t_philo		*first;
	int			counter;
	uint64_t	time;

	first = (t_philo *)((t_philos *)ptr)->first;
	counter = 0;
	while (counter != first->infos->table.num_philosophers)
	{
		counter = 0;
		philo = first;
		while (philo)
		{
			pthread_mutex_lock(&philo->state->lock);
			time = get_ms_time() - philo->state->time;
			if (philo->state->state != FULL
				&& time >= first->infos->time_to_die)
				return (finish(philo));
			else if (philo->state->state == FULL)
				counter++;
			pthread_mutex_unlock(&philo->state->lock);
			philo = philo->next;
		}
	}
	return (NULL);
}

void	launch_forks(t_philos *philos, t_infos *infos)
{
	int		i;
	t_philo	*philo;

	i = 1;
	infos->table.start = get_ms_time();
	while (i <= infos->table.num_philosophers)
	{
		philo = get_philo(philos, i);
		pthread_create(&philo->thread, NULL, dining, (void *)philo);
		i += 2;
	}
	i = 2;
	while (i <= infos->table.num_philosophers)
	{
		philo = get_philo(philos, i);
		pthread_create(&philo->thread, NULL, dining, (void *)philo);
		i += 2;
	}
}

void	wait_forks(t_philos *philos, t_infos *infos)
{
	int		counter;
	t_philo	*philo;

	counter = 1;
	while (counter <= infos->table.num_philosophers)
	{
		philo = get_philo(philos, counter);
		pthread_join(philo->thread, NULL);
		counter++;
	}
}

int	main(int argc, char *argv[])
{
	t_philos	*philos;
	t_philo		*philo;
	pthread_t	grim_reaper;
	t_forks		*forks;
	t_infos		*infos;

	if (argc == 0 || argv[0] == NULL)
		ft_usage(NULL, NULL, NULL);
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (infos == NULL)
		return (ft_error(NULL, NULL, NULL));
	if (init(argc, argv, infos) == -1)
		return (ft_usage(infos, NULL, NULL));
	forks = init_forks(infos->table.num_forks);
	if (!forks)
		return (ft_error(infos, NULL, NULL));
	philos = init_philos(infos->table.num_philosophers, infos, forks);
	if (!philos)
		return (ft_error(infos, forks, NULL));
	pthread_create(&grim_reaper, NULL, reaping, (void *)philos);
	pthread_detach(grim_reaper);
	launch_forks(philos, infos);
	wait_forks(philos, infos);
	ft_free(infos, forks, philos);
	return (0);
}
