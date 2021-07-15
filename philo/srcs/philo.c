/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/15 23:54:42 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*reaping(void *ptr)
{
	t_philo		*philo;
	t_philo		*first;
	int			counter;
	int			finished;
	uint64_t	time;
	int			state;

	first = (t_philo *)((t_philosophers *)ptr)->first;
	finished = 0;
	while (!finished)
	{
		counter = 0;
		philo = first;
		while (philo)
		{
			pthread_mutex_lock(&philo->state->lock);
			time = get_ms_time() - philo->state->time;
			if (philo->state->state != FULL && time >= first->constraints->time_to_die)
			{
				finished = dying(philo);
				philo = first;
				while (philo)
				{
					pthread_mutex_lock(&philo->state->lock);
					philo = philo->next;
				}
				philo = first;
				while (philo)
				{
					philo->state->state = DEAD;
					pthread_mutex_unlock(&philo->state->lock);
					philo = philo->next;
				}
				break ;
			}
			else if (philo->state->state == FULL)
				counter++;
			philo = philo->next;
		}
		if (counter == first->constraints->table.num_philosophers)
			finished = 1;
	}
	printf("hbruefuzbruvbezbvzuvbezuibvezvezvezvee");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philosophers	*philosophers;
	t_philo			*philo;
	pthread_t		grim_reaper;
	t_forks			*forks;
	int 			counter;
	t_constraints	*cons;

	if (argc == 0 || argv[0] == NULL)
		ft_usage(NULL);
	cons = (t_constraints *)malloc(sizeof(t_constraints));
	if (cons == NULL)
	{
		ft_error(NULL);
		return (1);
	}
	if (init(argc, argv, cons) == -1)
	{
		ft_usage(cons);
		return (1);
	}
	forks = initialize_forks(cons->table.num_forks);
	philosophers = initalize_philosophers(cons->table.num_philosophers, cons, forks);
	if (!forks || !philosophers)
	{
		ft_error(NULL);
		return (1);
	}
	counter = 0;
	cons->table.start = get_ms_time();
	while (counter < cons->table.num_philosophers)
	{
		philo = get_philo(philosophers, counter + 1);
		pthread_create(&philo->thread, NULL, dining, (void *)philo);
		counter++;
	}
	pthread_create(&grim_reaper, NULL, reaping, (void *)philosophers);
	counter = 0;
	while (counter < cons->table.num_philosophers)
	{
		philo = get_philo(philosophers, counter + 1);
		pthread_join(philo->thread, NULL);
		counter++;
	}
	pthread_join(grim_reaper, NULL);
	ft_free_constraints(cons);
	free_forks(forks);
	free_philosophers(philosophers);
	return (0);
}

//printf("philo %d || left_fork_index : %d || right_fork_index : %d\n", philo->id, philo->left_fork->index, philo->right_fork->index);