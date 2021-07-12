/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/12 14:08:25 by avogt            ###   ########.fr       */
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

enum statut { DEAD, EATING, SLEEPING, THINKING };

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
	double					time_to_think;
	int						nb_meal;
	t_table					table;
}							t_constraints;

typedef struct				s_philo
{
	struct s_constraints	*constraints;
	int						id;
	pthread_t				thread;
	double					time;
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

void						ft_putstr_fd(char *str);
int							ft_len(char *str);
void						ft_usage(t_constraints *c);
void						ft_error(t_constraints *c);
void						*thinking(void *s);
void						*sleeping(void *s);
void						*eating(void *s);
void						*dying(void *ptr);
void						*dining(void *ptr);
int							get_num_philosophers(char *str);
int							get_time(char *str);
uint64_t					get_ms_time(void);
int							init(int ac, char *av[], t_constraints *c);
void						ft_free_constraints(t_constraints *cons);
#endif
