/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/10 18:39:49 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*eating(void *ptr)
{
	t_philo *ph =  (t_philo *)ptr;
	printf("%ld philo%d is eating\n", get_ms_time() - ph->constraints->table.start, ph->id);
	return (NULL);
}

void	*sleeping(void *ptr)
{
	t_philo *ph =  (t_philo *)ptr;
	printf("%ld philo%d is sleeping\n", get_ms_time() - ph->constraints->table.start, ph->id);
	return (NULL);
}

void	*thinking(void *ptr)
{
	t_philo *ph =  (t_philo *)ptr;
	printf("%ld philo%d is thinking\n", get_ms_time() - ph->constraints->table.start, ph->id);
	return (NULL);
}

uint64_t	get_ms_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec *(uint64_t)1000) + (tv.tv_usec / 1000));
}
