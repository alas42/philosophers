/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 18:28:28 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	printing(philo, EATING);
	ft_usleep(get_ms_time(), philo->infos->time_to_eat);
}

void	sleeping(t_philo *philo)
{
	printing(philo, SLEEPING);
	ft_usleep(get_ms_time(), philo->infos->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	printing(philo, THINKING);
}

void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	printing(philo, TAKING_FORK);
}
