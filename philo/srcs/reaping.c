#include "../includes/philo.h"

int	check_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->info_philo);
	if (get_ms_time() - philo->time >= philo->infos->time_to_die)
	{
		pthread_mutex_unlock(philo->info_philo);
		printing(philo, DEAD, get_ms_time());
		return (1);
	}
	return (0);
}

void	*reaping(void *ptr)
{
	t_philo		*philos;
	int			i;
	int			counter;

	counter = 0;
	philos = (t_philo *)ptr;
	while (counter < philos[0].infos->num_philos)
	{
		i = -1;
		counter = 0;
		usleep(500);
		while (++i < philos[0].infos->num_philos)
		{
			if (philos[i].times_eating == philos[i].infos->nb_meal)
				counter++;
			else if (check_philo(&philos[i]))
				return (NULL);
			pthread_mutex_unlock(philos[i].info_philo);
		}
	}
	return (NULL);
}
