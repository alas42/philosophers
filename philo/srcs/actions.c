/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/24 12:08:36 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		philo->state->state = EATING;
		philo->state->time = get_ms_time();
		printing(philo, EATING);
		if (philo->infos->nb_meal > 0)
			philo->state->times_eating += 1;
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
		philo->state->state = SLEEPING;
		printing(philo, SLEEPING);
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
		philo->state->state = THINKING;
		printing(philo, THINKING);
	}
	pthread_mutex_unlock(&philo->state->lock);
}

void	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	printing(philo, TAKING_FORK);
}
