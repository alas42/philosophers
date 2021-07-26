/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:28:20 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 17:05:27 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_itoa_size(size_t n)
{
	int				size;

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

static char	*ft_itoa(size_t n)
{
	char			*str;
	int				i;
	int				size;
	unsigned int	tmp;

	size = ft_itoa_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 1;
	tmp = n;
	if (tmp == 0)
		str[0] = '0';
	while (tmp >= 1)
	{
		str[size - i] = (tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	str[size] = '\0';
	return (str);
}

static char	*ft_concat(char *time, char *id, char *message, char *action)
{
	int i;
	int	j;

	j = 0;
	i = 0;
	message = (char *)malloc(sizeof(char) * (10 + ft_len(id) + ft_len(action)));
	if (message == NULL)
		return (NULL);
	while (time[i])
	{
		message[i] = time[i];
		i++;
	}
	while (i < 9)
		message[i++] = ' ';
	while (id[j] != '\0')
		message[i++] = id[j++];
	j = 0;
	while (action[j] != '\0')
		message[i++] = action[j++];
	message[i] = '\0';
	return (message);
}

static void	get_print_message(t_philo *philo, size_t time, int action)
{
	char	*str[6];
	char	*time_str;
	char	*philo_str;
	char	*message;

	str[0] = " died\n";
	str[1] = " is eating\n";
	str[2] = " is sleeping\n";
	str[3] = " is thinking\n";
	str[4] = " has taken a fork\n";
	str[5] = " is satiated\n";
	time_str = ft_itoa(time);
	philo_str = ft_itoa(philo->id);
	message = NULL;
	message = ft_concat(time_str, philo_str, message, str[action]);
	free(time_str);
	free(philo_str);
	if (message == NULL)
		return ;
	write(1, message, ft_len(message));
	free(message);
}

void	printing(t_philo *philo, int action)
{
	size_t	time;

	philo->state = action;
	time = get_ms_time();
	if (action == EATING)
		philo->time = time;
	pthread_mutex_lock(&philo->infos->print);
	if (!philo->infos->finished)
	{
		philo->state = action;
		get_print_message(philo, time - philo->infos->start, action);
	}
	pthread_mutex_unlock(&philo->infos->print);
	if (action == DEAD)
		philo->infos->finished = 1;
	if (philo->infos->finished)
		philo->state = DEAD;
}
