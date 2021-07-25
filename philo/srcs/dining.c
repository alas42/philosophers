/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/25 17:14:52 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->state->lock);
	return (0);
}

static int	is_full(t_philo *philo)
{
	if (philo->infos->nb_meal > 0)
	{
		philo->state->times_eating += 1;
		if (philo->state->times_eating == philo->infos->nb_meal)
		{
			philo->state->state = FULL;
			pthread_mutex_unlock(&philo->state->lock);
			printing(philo, FULL);
			return (1);
		}
	}
	return (0);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		take_fork(philo, philo->left_fork);
		if (philo->right_fork != NULL)
			take_fork(philo, philo->right_fork);
		else
		{
			while (1)
			{
				if (is_dead(philo))
					return ;
				usleep(200);
			}
		}
		return ;
	}
	take_fork(philo, philo->right_fork);
	take_fork(philo, philo->left_fork);
}

static void	depose_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
		if (philo->right_fork != NULL)
			pthread_mutex_unlock(&philo->right_fork->lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_unlock(&philo->left_fork->lock);
	}
}

void	*dining(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (!(philo->id % 2) || philo->id == philo->infos->table.num_philos)
		usleep(500);
	while (1)
	{
		if (is_dead(philo))
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
