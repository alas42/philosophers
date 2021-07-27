/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:28:20 by avogt             #+#    #+#             */
/*   Updated: 2021/07/27 15:42:01 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_itoa_size(unsigned long long n)
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

static void	ft_itoa(unsigned long long n, char *message, int *j)
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

static void	ft_concat(unsigned long long time, int id, char *message, char *action)
{
	int i;
	int	j;

	j = 0;
	i = 0;
	ft_itoa(time, message, &i);
	while (i < 9)
		message[i++] = ' ';
	ft_itoa(id, message, &i);
	j = 0;
	while (action[j] != '\0')
		message[i++] = action[j++];
	message[i] = '\0';
}

static char	*print_message(t_philo *philo, unsigned long long time, int action)
{
	char	*str[6];
	char	*message;

	str[0] = " died\n";
	str[1] = " is eating\n";
	str[2] = " is sleeping\n";
	str[3] = " is thinking\n";
	str[4] = " has taken a fork\n";
	str[5] = " is satiated\n";

	message = (char *)malloc(sizeof(char) * 33);
	if (!message)
		return (NULL);
	ft_concat(time, philo->id, message, str[action]);
	return (message);
}

int	printing(t_philo *philo, int action, unsigned long long time)
{
	char	*str;

	str = NULL;
	pthread_mutex_lock(philo->print);
	if (!philo->infos->finished)
	{
		if (action == EATING)
			philo->time = time;
		str = print_message(philo, time - philo->infos->start, action);
		write(1, str, ft_len(str));
		free(str);
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
