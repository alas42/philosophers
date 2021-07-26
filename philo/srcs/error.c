/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:39:52 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 18:20:56 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_usage(t_infos *infos, pthread_mutex_t *f, t_philo *ps)
{
	char	*s1;
	char	*s2;

	s1 = "Error\nusage: nb_philo time_to_die time_to_eat time_to_sleep ";
	s2 = "[number_of_times_each_philosopher_must_eat]\n";
	ft_free(infos, f, ps);
	write(2, s1, ft_len(s1));
	write(2, s2, ft_len(s2));
	return (1);
}

int	ft_error(t_infos *infos, pthread_mutex_t *f, t_philo *ps)
{
	ft_free(infos, f, ps);
	write(2, "Error\n", ft_len("Error\n"));
	return (1);
}
