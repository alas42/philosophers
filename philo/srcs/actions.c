/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/25 17:12:56 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		philo->state->state = EATING;
		printing(philo, EATING);
		pthread_mutex_unlock(&philo->state->lock);
		ft_usleep(philo->infos->time_to_eat);
	}
	else
		pthread_mutex_unlock(&philo->state->lock);
}

void	sleeping(t_philo *philo)
{
	if (philo->state->state != DEAD)
	{
		philo->state->state = SLEEPING;
		printing(philo, SLEEPING);
		pthread_mutex_unlock(&philo->state->lock);
		ft_usleep(philo->infos->time_to_sleep);
	}
	else
		pthread_mutex_unlock(&philo->state->lock);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		philo->state->state = THINKING;
		printing(philo, THINKING);
		pthread_mutex_unlock(&philo->state->lock);
	}
	else
		pthread_mutex_unlock(&philo->state->lock);
}

void	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	pthread_mutex_lock(&philo->state->lock);
	printing(philo, TAKING_FORK);
	pthread_mutex_unlock(&philo->state->lock);
}
