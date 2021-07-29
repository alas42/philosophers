/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/29 11:39:05 by avogt            ###   ########.fr       */
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
	char			*str;
	int				num_philos;
	long long		start;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_meal;
	int				finished;
}					t_infos;

typedef struct s_philo
{	
	struct s_infos	*infos;
	int				id;
	long long		time;
	int				times_eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*info_philo;
	pthread_mutex_t	*print;
}					t_philo;

int					thinking(t_philo *ptr);
int					sleeping(t_philo *ptr);
int					eating(t_philo *ptr);
int					is_full(t_philo *philo);
int					take_forks(t_philo *philo);
void				depose_forks(t_philo *philo);
void				*dining(void *ptr);
void				take_fork(t_philo *philo, pthread_mutex_t *fork);
int					get_num_philosophers(char *str);
long long			get_time(char *str);
long long			get_ms_time(void);
int					ft_len(char *str);
int					printing(t_philo *philo, int action, long long time);
int					init(int ac, char *av[], t_infos *infos);
t_philo				*init_philos(t_infos *i,
						pthread_mutex_t *fs, pthread_mutex_t *print,
						pthread_mutex_t *i_p);
pthread_mutex_t		*init_forks(int nb);
void				ft_free(t_infos *i, pthread_mutex_t *f, t_philo *ps);
void				free_philos(t_philo *p, int n);
void				free_forks(pthread_mutex_t *f, int n);
int					ft_usage(t_infos *i, pthread_mutex_t *f, t_philo *ps);
int					ft_error(t_infos *i, pthread_mutex_t *f, t_philo *ps);
int					ft_usleep(long long t, long long desired_t, t_philo *p);
void				init_time(t_philo *philo);
#endif
