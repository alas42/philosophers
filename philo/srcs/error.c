/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:39:52 by avogt             #+#    #+#             */
/*   Updated: 2021/07/15 21:00:56 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usage(t_constraints *cons)
{
	if (cons)
		ft_free_constraints(cons);
	printf("Error\nusage: nb_philo time_to_die time_to_eat time_to_sleep (n_eating_before_ending)\nthe time shall be given in milliseconds without point or other characters");
}

void	ft_error(t_constraints *cons)
{
	if (cons)
		ft_free_constraints(cons);
	printf("Error\n");
}
