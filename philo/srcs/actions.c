/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/29 11:35:55 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_philo *philo)
{
	long long	time;

	time = get_ms_time();
	if (printing(philo, EATING, time))
		return (1);
	if (ft_usleep(time, philo->infos->time_to_eat, philo))
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	time;

	time = get_ms_time();
	if (printing(philo, SLEEPING, time))
		return (1);
	if (ft_usleep(time, philo->infos->time_to_sleep, philo))
		return (1);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (printing(philo, THINKING, get_ms_time()))
		return (1);
	return (0);
}

void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	printing(philo, TAKING_FORK, get_ms_time());
}
