/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:28:20 by avogt             #+#    #+#             */
/*   Updated: 2021/07/25 17:11:16 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_message(t_philo *philo, unsigned long time, int action)
{
	if (action == EATING)
	{
		printf("%ld%s %d is eating\n", time, "\t", philo->id);
		philo->state->time = time;
	}
	else if (action == SLEEPING)
		printf("%ld%s %d is sleeping\n", time, "\t", philo->id);
	else if (action == THINKING)
		printf("%ld%s %d is thinking\n", time, "\t", philo->id);
	else if (action == TAKING_FORK)
		printf("%ld%s %d has taken a fork\n", time, "\t", philo->id);
	else if (action == FULL)
		printf("%ld%s %d is satiated\n", time, "\t", philo->id);
}

void		printing(t_philo *philo, int action)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->infos->lock);
	time = get_ms_time() - philo->infos->table.start;
	if (!philo->infos->finished)
	{
		print_message(philo, time, action);
	}
	if (action == DEAD)
	{
		philo->infos->finished = 1;
		printf("%ld%s %d died\n", time, "\t", philo->id);
	}
	if (philo->infos->finished)
	{
		philo->state->state = DEAD;
	}
	pthread_mutex_unlock(&philo->infos->lock);
}
