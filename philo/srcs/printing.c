/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:28:20 by avogt             #+#    #+#             */
/*   Updated: 2021/07/24 12:21:02 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	printing(t_philo *philo, int action)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->infos->lock);
	time = get_ms_time() - philo->infos->table.start;
	if (!philo->infos->finished)
	{
		if (action == EATING)
			printf("%ld%s %d is eating\n", time, "\t", philo->id);
		else if (action == SLEEPING)
			printf("%ld%s %d is sleeping\n", time, "\t", philo->id);
		else if (action == THINKING)
			printf("%ld%s %d is thinking\n", time, "\t", philo->id);
		else if (action == TAKING_FORK)
			printf("%ld%s %d has taken a fork\n", time, "\t", philo->id);
		else if (action == FULL)
			printf("%ld%s %d is satiated\n", time, "\t", philo->id);
	}
	if (action == DEAD)
	{
		philo->infos->finished = 1;
		printf("%ld%s %d died\n", time, "\t", philo->id);
	}
	if (philo->infos->finished)
		philo->state->state = DEAD;
	pthread_mutex_unlock(&philo->infos->lock);
}
