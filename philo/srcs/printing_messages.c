/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:52:44 by avogt             #+#    #+#             */
/*   Updated: 2021/07/11 18:47:02 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*eating(void *ptr)
{
	t_philo	*ph = (t_philo *)ptr;
	printf("%ld%s %d is eating\n", get_ms_time() - ph->constraints->table.start, "\t", ph->id);
	return (NULL);
}

void	*sleeping(void *ptr)
{
	t_philo	*ph = (t_philo *)ptr;
	printf("%ld%s %d is sleeping\n", get_ms_time() - ph->constraints->table.start, "\t", ph->id);
	return (NULL);
}

void	*thinking(void *ptr)
{
	t_philo	*ph = (t_philo *)ptr;
	printf("%ld%s %d is thinking\n", get_ms_time() - ph->constraints->table.start, "\t", ph->id);
	return (NULL);
}

void	*dying(void *ptr)
{
	t_philo	*ph = (t_philo *)ptr;
	printf("%ld%s %d died\n", get_ms_time() - ph->constraints->table.start, "\t", ph->id);
	return (NULL);
}
