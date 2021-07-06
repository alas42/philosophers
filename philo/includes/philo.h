/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/06 11:23:53 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

enum statut { DEAD, EATING, SLEEPING, THINKING };

typedef struct			s_table
{
	int					num_forks;
	int					num_philosophers;
}						t_table;

typedef struct			s_constraints
{
	double				time_to_die;
	double				time_to_eat;
	double				time_to_think;
	int					times_eating;
	t_table				table;
}						t_constraints;

typedef struct			s_philo
{
	pthread_t			thread;
	int					id;
}						t_philo;

void					ft_putstr_fd(char *str);
int						ft_len(char *str);
void					ft_usage(void);
void					ft_error(void);
void					*thinking(void *s);
void					*sleeping(void *s);
void					*eating(void *s);
int						get_num_philosophers(char *str);
int						get_time(char *str);
double					get_ms_time(struct timeval start);
int						init(int ac, char *av[], t_constraints *c);
void					ft_free_constraints(t_constraints *cons);
#endif