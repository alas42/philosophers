/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:39:52 by avogt             #+#    #+#             */
/*   Updated: 2021/06/21 17:30:11 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usage(void)
{
	printf("Error\nusage: nb_philo time_to_die time_to_eat time_to_sleep (n_eating_before_ending)\nthe time shall be given in milliseconds without point or other characters");
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}