/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/26 18:30:43 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

enum e_statut { DEAD, EATING, SLEEPING, THINKING, TAKING_FORK, FULL };

typedef struct s_infos
{
	int						num_philos;
	size_t					start;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	int						nb_meal;
	pthread_mutex_t			print;
	int						finished;
}							t_infos;

typedef struct s_philo
{	
	struct s_infos			*infos;
	int						id;
	size_t					time;
	int						times_eating;
	int						state;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
}							t_philo;

void						thinking(t_philo *ptr);
void						sleeping(t_philo *ptr);
void						eating(t_philo *ptr);
int							is_full(t_philo *philo);
void						take_forks(t_philo *philo);
void						depose_forks(t_philo *philo);
void						*dining(void *ptr);
void						take_fork(t_philo *philo, pthread_mutex_t *fork);
int							get_num_philosophers(char *str);
int							get_time(char *str);
size_t						get_ms_time(void);
int							ft_len(char *str);
void						printing(t_philo *philo, int action);
int							init(int ac, char *av[], t_infos *infos);
t_philo						*init_philos(int nb, t_infos *infos, pthread_mutex_t *fs);
pthread_mutex_t				*init_forks(int nb);
void						ft_free(t_infos *infos, pthread_mutex_t *f, t_philo *ps);
void						free_philos(t_philo *p);
void						free_forks(pthread_mutex_t *f, int n);
int							ft_usage(t_infos *infos, pthread_mutex_t *f, t_philo *ps);
int							ft_error(t_infos *infos, pthread_mutex_t *f, t_philo *ps);
void						ft_usleep(size_t time, size_t desired_time);
#endif
