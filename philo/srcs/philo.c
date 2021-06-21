/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/06/21 17:29:19 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating(void *s)
{
	printf("%s - eating\n", (char *)s);
	return (NULL);
}

void	*sleeping(void *s)
{
	printf("%s - sleeping\n", (char *)s);
	return (NULL);
}

void	*thinking(void *s)
{
	printf("%s - thinking\n", (char *)s);
	return (NULL);
}

double	get_ms_time(struct timeval start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - start.tv_sec) + (tv.tv_usec - start.tv_usec)
			/ 1000.0);
}

int	main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	int	ret1, ret2;
	struct timeval start_tv;
	t_table *table;
	t_constraints *cons;

	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		ft_error();
	cons = (t_constraints *)malloc(sizeof(t_constraints));
	if (cons == NULL)
		ft_error();
	if (init(argc, argv, table, cons) == -1)
		ft_usage();
	gettimeofday(&start_tv, NULL);
	ret1 = 0;
	ret2 = 0;
	if (argc == 0 || argv[0] == NULL)
		ft_usage();
	ret1 = pthread_create(&thread1, NULL, eating, (void *)"1");
	ret2 = pthread_create(&thread2, NULL, thinking, (void *)"2");
 	pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
	usleep(1000);
	printf("%lf Thread 1 returns: %d\n", get_ms_time(start_tv), ret1);
	usleep(1000);
	printf("%lf Thread 2 returns: %d\n", get_ms_time(start_tv), ret2);
	return (0);
}