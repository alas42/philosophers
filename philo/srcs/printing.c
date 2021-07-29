/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:28:20 by avogt             #+#    #+#             */
/*   Updated: 2021/07/29 13:32:52 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_itoa_size(long long n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void	ft_itoa(long long n, char *message, int *j)
{
	int	size;

	size = *j + ft_itoa_size(n);
	if (n == 0)
	{
		message[*j] = '0';
		*j = *j + 1;
	}
	while (n >= 1)
	{
		message[--size] = (n % 10) + '0';
		n /= 10;
		*j = *j + 1;
	}
	message[*j] = '\0';
}

static void	print_message(t_philo *philo, long long time, int action)
{
	char	*str[6];
	int		i;
	int		j;

	i = 0;
	str[0] = " died\n0";
	str[1] = " is eating\n0";
	str[2] = " is sleeping\n0";
	str[3] = " is thinking\n0";
	str[4] = " has taken a fork\n0";
	str[5] = " is satiated\n0";
	ft_itoa(time, philo->infos->str, &i);
	while (i < 9)
		philo->infos->str[i++] = ' ';
	ft_itoa(philo->id, philo->infos->str, &i);
	j = 0;
	while (str[action][j] != '0')
		philo->infos->str[i++] = str[action][j++];
	philo->infos->str[i] = '\0';
}

int	printing(t_philo *philo, int action, long long time)
{
	pthread_mutex_lock(philo->print);
	if (!philo->infos->finished)
	{
		pthread_mutex_lock(philo->info_philo);
		if (time - philo->time > philo->infos->time_to_die)
			action = DEAD;
		if (action == EATING)
			philo->time = time;
		pthread_mutex_unlock(philo->info_philo);
		print_message(philo, time - philo->infos->start, action);
		write(1, philo->infos->str, ft_len(philo->infos->str));
	}
	if (action == DEAD)
		philo->infos->finished = 1;
	if (philo->infos->finished)
	{
		pthread_mutex_unlock(philo->print);
		return (1);
	}
	pthread_mutex_unlock(philo->print);
	return (0);
}
