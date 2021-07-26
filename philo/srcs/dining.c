/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 18:28:18 by avogt            ###   ########.fr       */
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

void	take_forks(t_philo *philo)
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
				if (philo->state == DEAD)
					return ;
				usleep(200);
			}
		}
		return ;
	}
	take_fork(philo, philo->right_fork);
	take_fork(philo, philo->left_fork);
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
	philo->time = get_ms_time();
	if (philo->id == philo->infos->num_philos)
		ft_usleep(get_ms_time(), 1);
	while (1)
	{
		if (philo->state == DEAD)
			break ;
		take_forks(philo);
		eating(ptr);
		depose_forks(philo);
		if (is_full(philo))
			break ;
		sleeping(ptr);
		thinking(ptr);
	}
	return (NULL);
}
