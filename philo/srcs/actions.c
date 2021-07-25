/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/18 18:08:25 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		pthread_mutex_lock(&philo->infos->lock);
		philo->state->state = EATING;
		printing(philo, EATING);
		if (philo->infos->nb_meal > 0)
			philo->state->times_eating += 1;
		philo->state->time = get_ms_time();
		pthread_mutex_unlock(&philo->infos->lock);
		pthread_mutex_unlock(&philo->state->lock);
		usleep(philo->infos->time_to_eat * 1000);
	}
	else
		pthread_mutex_unlock(&philo->state->lock);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		pthread_mutex_lock(&philo->infos->lock);
		philo->state->state = SLEEPING;
		printing(philo, SLEEPING);
		pthread_mutex_unlock(&philo->infos->lock);
		pthread_mutex_unlock(&philo->state->lock);
		usleep(philo->infos->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&philo->state->lock);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		pthread_mutex_lock(&philo->infos->lock);
		philo->state->state = THINKING;
		printing(philo, THINKING);
		pthread_mutex_unlock(&philo->infos->lock);
	}
	pthread_mutex_unlock(&philo->state->lock);
}

void	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	pthread_mutex_lock(&philo->state->lock);
	pthread_mutex_lock(&philo->infos->lock);
	printing(philo, TAKING_FORK);
	pthread_mutex_unlock(&philo->infos->lock);
	pthread_mutex_unlock(&philo->state->lock);
}
