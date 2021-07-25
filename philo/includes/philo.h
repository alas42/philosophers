/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/25 17:05:20 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

enum e_statut { DEAD, EATING, SLEEPING, THINKING, TAKING_FORK, FULL };

typedef struct s_table
{
	int						num_philos;
	unsigned long				start;
}							t_table;

typedef struct s_infos
{
	unsigned long			time_to_die;
	unsigned long				time_to_eat;
	unsigned long				time_to_sleep;
	int						nb_meal;
	t_table					table;
	pthread_mutex_t			lock;
	int						finished;
}							t_infos;

typedef struct s_state
{
	pthread_mutex_t			lock;
	unsigned long				time;
	int						times_eating;
	int						state;
}							t_state;

typedef struct s_philo
{
	struct s_infos			*infos;
	int						id;
	struct s_state			*state;
	pthread_t				thread;
	struct s_fork			*left_fork;
	struct s_fork			*right_fork;
	struct s_philo			*next;
}							t_philo;

typedef struct s_philos
{
	struct s_philo			*first;
}							t_philos;

typedef struct s_fork
{
	int						index;
	int						taken;
	pthread_mutex_t			lock;
	struct s_fork			*next;
}							t_fork;

typedef struct s_forks
{
	struct s_fork			*first;
}							t_forks;

int							ft_usage(t_infos *infos, t_forks *f, t_philos *ps);
int							ft_error(t_infos *infos, t_forks *f, t_philos *ps);

void						thinking(t_philo *ptr);
void						sleeping(t_philo *ptr);
void						eating(t_philo *ptr);
void						*dining(void *ptr);
void						take_fork(t_philo *philo, t_fork *fork);

int							get_num_philosophers(char *str);
int							get_time(char *str);
unsigned long					get_ms_time(void);
int							ft_len(char *str);
void						printing(t_philo *philo, int action);

t_fork						*get_fork_ptr(t_forks *forks, int index);
t_philo						*get_philo(t_philos *p, int index);
t_state						*get_state_ptr(void);

int							init(int ac, char *av[], t_infos *infos);
int							add_to_philos(t_philos *p, int index,
								t_infos *infos, t_forks *forks);
int							add_to_forks(t_forks *f, int index);
t_philos					*init_philos(int nb, t_infos *infos, t_forks *fs);
t_forks						*init_forks(int nb);
void						ft_free(t_infos *infos, t_forks *f, t_philos *ps);
void						free_philos(t_philos *p);
void						free_forks(t_forks *f);
void						ft_usleep(unsigned long time);
#endif
