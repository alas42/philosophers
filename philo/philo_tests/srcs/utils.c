/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 21:59:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/24 11:35:47 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

uint64_t	get_ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec *(uint64_t)1000) + (tv.tv_usec / 1000));
}

t_fork	*get_fork_ptr(t_forks *forks, int index)
{
	t_fork	*fork;

	fork = forks->first;
	while (fork->index != index)
		fork = fork->next;
	return (fork);
}

t_state	*get_state_ptr(void)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	if (state == NULL)
		return (NULL);
	pthread_mutex_init(&state->lock, NULL);
	state->times_eating = 0;
	state->state = THINKING;
	state->time = get_ms_time();
	return (state);
}

t_philo	*get_philo(t_philos *p, int index)
{
	t_philo	*philo;

	philo = p->first;
	while (philo != NULL)
	{
		if (philo->id == index)
			return (philo);
		philo = philo->next;
	}
	return (philo);
}
