/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:23 by avogt             #+#    #+#             */
/*   Updated: 2021/07/10 18:37:48 by avogt            ###   ########.fr       */
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

typedef struct			s_table
{
	int					num_forks;
	int					num_philosophers;
	uint64_t 			start;
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
	struct s_constraints *constraints;
	int					id; //number of philo -> will be used for printing
	pthread_t			thread; // the thread in itself maybe not here
	double				time; //time -> because I want to access it from inside the thread function
	int					index_forks[2]; // TO KNOW and search for the right forks
	struct s_philo		*next; // ptr to next philo
}						t_philo;

typedef struct			s_philosophers
{
	struct s_philo		*first;
}						t_philosophers;

void					ft_putstr_fd(char *str);
int						ft_len(char *str);
void					ft_usage(t_constraints *c);
void					ft_error(t_constraints *c);
void					*thinking(void *s);
void					*sleeping(void *s);
void					*eating(void *s);
int						get_num_philosophers(char *str);
int						get_time(char *str);
uint64_t				get_ms_time(void);
int						init(int ac, char *av[], t_constraints *c);
void					ft_free_constraints(t_constraints *cons);
#endif
