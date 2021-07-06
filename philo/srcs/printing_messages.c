/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/06 11:19:02 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*eating(void *id)
{
	printf("philo%d is eating\n", *(int *)id);
	return (NULL);
}

void	*sleeping(void *id)
{
	printf("philo%d is sleeping\n", *(int *)id);
	return (NULL);
}

void	*thinking(void *id)
{
	printf("philo%d is thinking\n", *(int *)id);
	return (NULL);
}

double	get_ms_time(struct timeval start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - start.tv_sec) + (tv.tv_usec - start.tv_usec)
			/ 1000.0);
}
