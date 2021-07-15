/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/15 23:58:33 by avogt            ###   ########.fr       */
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

enum statut { DEAD, EATING, SLEEPING, THINKING, FULL };

typedef struct				s_table
{
	int						num_forks;
	int						num_philosophers;
	uint64_t 				start;
}							t_table;

typedef struct				s_constraints
{
	double					time_to_die;
	double					time_to_eat;
	double					time_to_sleep;
	int						nb_meal;
	t_table					table;
}							t_constraints;

typedef struct				s_state
{
	pthread_mutex_t			lock;
	uint64_t				time;
	int						state;
}							t_state;

typedef struct				s_philo
{
	struct s_constraints	*constraints;
	int						id;
	struct s_state			*state;
	pthread_t				thread;
	struct s_fork			*left_fork;
	struct s_fork			*right_fork;
	int						times_eating;
	struct s_philo			*next;
}							t_philo;

typedef struct				s_philosophers
{
	struct s_philo			*first;
}							t_philosophers;

typedef struct				s_fork
{
	int						index;
	int						taken;
	pthread_mutex_t			lock;
	struct s_fork			*next;
}							t_fork;

typedef struct				s_forks
{
	struct s_fork			*first;
}							t_forks;
//			ERRORS
void						ft_usage(t_constraints *c);
void						ft_error(t_constraints *c);
//			MESSAGES AND CORE THREAD PROGRAM
void						thinking(t_philo *ptr);
void						take_fork(t_philo *ptr);
void						depose_fork(t_philo *philo);
void						sleeping(t_philo *ptr);
void						eating(t_philo *ptr);
int							dying(t_philo *philo);
void						*dining(void *ptr);
//			UTILS
int							get_num_philosophers(char *str);
int							get_time(char *str);
uint64_t					get_ms_time(void);
int							ft_len(char *str);
//			GETTERS
t_fork						*get_fork_ptr(t_forks *forks, int index);
t_philo						*get_philo(t_philosophers *p, int index);
t_state						*get_state_ptr(void);
//			INITIALIZE
int							init(int ac, char *av[], t_constraints *c);
int	add_to_philosophers(t_philosophers *p, int index, t_constraints *cons, t_forks *forks);
int	add_to_forks(t_forks *f, int index);
t_philosophers	*initalize_philosophers(int nb, t_constraints *cons, t_forks *forks);
t_forks	*initialize_forks(int nb);
//			FREES
void						ft_free_constraints(t_constraints *cons);
void						free_philosophers(t_philosophers *p);
void						free_forks(t_forks *f);
#endif
