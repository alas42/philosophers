/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:59:13 by avogt             #+#    #+#             */
/*   Updated: 2021/07/24 10:40:57 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_num_philosophers(char *str)
{
	int	i;
	int	other;
	int	num_philo;

	num_philo = 0;
	other = 0;
	i = -1;
	while (str[++i] != '\0')
		if (!(str[i] <= '9' && str[i] >= '0'))
			other = 1;
	if (other != 0 || i == 0)
		return (-1);
	i = -1;
	while (str[++i] != '\0')
	{
		num_philo *= 10;
		num_philo += (str[i] - '0');
	}
	return (num_philo);
}

int	get_time(char *str)
{
	int	time;
	int	i;
	int	other;

	time = 0;
	i = -1;
	other = 0;
	while (str[++i] != '\0')
		if (!(str[i] <= '9' && str[i] >= '0'))
			other = 1;
	if (other != 0 || i == 0)
		return (-1);
	i = -1;
	while (str[++i] != '\0')
	{
		time *= 10;
		time += (str[i] - '0');
	}
	return (time);
}
