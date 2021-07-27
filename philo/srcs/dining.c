/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/27 13:52:35 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_full(t_philo *philo)
{
	if (philo->infos->nb_meal > 0)
	{
		philo->times_eating += 1;
		if (philo->times_eating == philo->infos->nb_meal)
		{
			printing(philo, FULL);
			return (1);
		}
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		take_fork(philo, philo->left_fork);
		if (philo->infos->num_philos != 1)
			take_fork(philo, philo->right_fork);
		else
		{
			while (1)
			{
				if (ft_usleep(get_ms_time(), 1, philo))
					return (1);
				usleep(200);
			}
		}
		return (0);
	}
	take_fork(philo, philo->right_fork);
	take_fork(philo, philo->left_fork);
	return (0);
}

void	depose_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		if (philo->infos->num_philos != 1)
			pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	*dining(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
//	pthread_mutex_lock(&philo->mutex_time);
	philo->time = get_ms_time();
//	pthread_mutex_unlock(&philo->mutex_time);
	if (philo->id == philo->infos->num_philos)
		ft_usleep(get_ms_time(), 1, philo);
	while (1)
	{
		if (take_forks(philo))
			break ;
		if (eating(ptr))
		{
			depose_forks(philo);
			printing(philo, DEAD);
			break;
		}
		depose_forks(philo);
		if (is_full(philo) || sleeping(philo) || thinking(philo))
		{
			printing(philo, DEAD);
			break ;
		}
	}
	return (NULL);
}
