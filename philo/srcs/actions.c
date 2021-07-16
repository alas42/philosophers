/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/16 18:56:30 by avogt            ###   ########.fr       */
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
		if (philo->constraints->nb_meal > 0)
			philo->times_eating += 1;
		philo->state->time = get_ms_time();
		pthread_mutex_unlock(&philo->state->lock);
		usleep(philo->constraints->time_to_eat * 1000);
	}
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
		usleep(philo->constraints->time_to_sleep * 1000);
	}
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

int		dying(t_philo *philo)
{
	printing(philo, DEAD);
	pthread_mutex_unlock(&philo->state->lock);
	return (1);
}

void	take_fork(t_philo *philo)
{
	printing(philo, TAKING_FORK);
}
