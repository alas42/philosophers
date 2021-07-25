/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/18 18:08:42 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	permission_print(t_philo *philo)
{
	int	ret;
	int	state;

	ret = 0;
	pthread_mutex_lock(&philo->state->lock);
	pthread_mutex_lock(&philo->infos->lock);
	state = philo->state->state;
	if (state == DEAD || state == FULL || philo->infos->finished)
		ret = 1;
	pthread_mutex_unlock(&philo->infos->lock);
	pthread_mutex_unlock(&philo->state->lock);
	return (ret);
}

static void	take_forks(t_philo *philo)
{
	int		lefty;

	lefty = philo->id % 2;
	if (lefty)
	{
		take_fork(philo, philo->left_fork);
		if (philo->right_fork != NULL)
			take_fork(philo, philo->right_fork);
		else
		{
			while (1)
			{
				pthread_mutex_lock(&philo->state->lock);
				if (philo->state->state == DEAD)
				{
					pthread_mutex_unlock(&philo->state->lock);
					return ;
				}
				pthread_mutex_unlock(&philo->state->lock);
				usleep(200);
			}
		}
	}
	else
	{
		take_fork(philo, philo->right_fork);
		take_fork(philo, philo->left_fork);
	}
}

static void	depose_forks(t_philo *philo)
{
	int		lefty;

	lefty = philo->id % 2;
	if (lefty)
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
	int		condition;

	philo = (t_philo *)ptr;
	condition = 1;
	while (condition)
	{
		if (permission_print(philo))
			break ;
		take_forks(philo);
		eating(ptr);
		depose_forks(philo);
		pthread_mutex_lock(&philo->state->lock);
		if (philo->state->times_eating == philo->infos->nb_meal)
		{
			philo->state->state = FULL;
			printing(philo, FULL);
			pthread_mutex_unlock(&philo->state->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->state->lock);
		sleeping(ptr);
		thinking(ptr);
		usleep(100);
	}
	return (NULL);
}
