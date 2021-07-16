/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/16 19:06:41 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	permission_print(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->state->lock);
	pthread_mutex_lock(&philo->constraints->lock);
	if (philo->state->state == DEAD || philo->state->state == FULL || philo->constraints->finished)
		ret = 1;
	pthread_mutex_unlock(&philo->constraints->lock);
	pthread_mutex_unlock(&philo->state->lock);
	return (ret);
}

static void	take_forks(t_philo *philo)
{
	int		lefty;

	lefty = philo->id % 2;
	pthread_mutex_lock(&philo->state->lock);
	if (lefty)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		take_fork(philo);
		pthread_mutex_lock(&philo->right_fork->lock);
		take_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->lock);
		take_fork(philo);
		pthread_mutex_lock(&philo->left_fork->lock);
		take_fork(philo);
	}
	pthread_mutex_unlock(&philo->state->lock);
}

static void	depose_forks(t_philo *philo)
{
	int		lefty;

	lefty = philo->id % 2;
	if (lefty)
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
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
		if (philo->times_eating == philo->constraints->nb_meal)
		{
			pthread_mutex_lock(&philo->state->lock);
			philo->state->state = FULL;
			printing(philo, FULL);
			pthread_mutex_unlock(&philo->state->lock);
			break ;
		}
		sleeping(ptr);
		thinking(ptr);
	}
	return (NULL);
}
