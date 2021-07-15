/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/15 23:58:21 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		time = get_ms_time() - philo->constraints->table.start;
		philo->state->state = EATING;
		printf("%ld%s %d is eating\n", time, "\t", philo->id);
		philo->state->time = get_ms_time();
		philo->times_eating += 1;
		usleep(philo->constraints->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philo->state->lock);
}

void	sleeping(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		time = get_ms_time() - philo->constraints->table.start;
		philo->state->state = SLEEPING;
		printf("%ld%s %d is sleeping\n", time, "\t", philo->id);
		usleep(philo->constraints->time_to_sleep * 1000);
	}
	pthread_mutex_unlock(&philo->state->lock);
}

void	thinking(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->state->lock);
	if (philo->state->state != DEAD)
	{
		time = get_ms_time() - philo->constraints->table.start;
		philo->state->state = THINKING;
		printf("%ld%s %d is thinking\n", time, "\t", philo->id);
	}
	pthread_mutex_unlock(&philo->state->lock);
}

int		dying(t_philo *philo)
{
	printf("%ld%s %d died\n", get_ms_time() - philo->constraints->table.start, "\t", philo->id);
	philo->state->state = DEAD;
	pthread_mutex_unlock(&philo->state->lock);
	return (1);
}

void	take_fork(t_philo *philo)
{
	uint64_t	time;

	time = get_ms_time() - philo->constraints->table.start;
	printf("%ld%s %d has taken a fork\n", time, "\t", philo->id);
}

void	depose_fork(t_philo *philo)
{
	uint64_t	time;

	time = get_ms_time() - philo->constraints->table.start;
	printf("%ld%s %d has deposed a fork\n", time, "\t", philo->id);
}