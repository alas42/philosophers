/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:17 by avogt             #+#    #+#             */
/*   Updated: 2021/07/12 14:21:44 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*dining(void *ptr)
{
	t_philo *philo = (t_philo *)ptr;
	t_fork	*f0;
	t_fork	*f1;
	while (philo->times_eating < philo->constraints->nb_meal || philo->constraints->nb_meal <= 0)
	{
		//if (!)
		//SHOULD LOOK WHEN HE IS DEAD
		//lock mutexs, one for each fork and print "taken a fork"
		//eat --usleep(time_to_eat)
		//unlock mutexs, one for each fork and print "returned the fork"
		//sleeping --usleep(time_to_sleep)
		//thinking till he can eat : mutex_try_unlock
		philo->times_eating += 1;
	}
	return (NULL);
}