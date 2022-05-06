#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (get_tm() - philo->last_eat_tm >= philo->time_to_die)
	{
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->dead);
}

static int	is_satisfied(t_params *data, int i, int *total)
{
	int	have;
	int	need;

	pthread_mutex_lock(data->philos[i].synchro);
    have = data->philos[i].cnt_eatings;
	need = data->philos[i].max_eatings;
	if (have >= need && need > 0)
		(*total)++;
	pthread_mutex_unlock(data->philos[i].synchro);
	if (*total == data->num_of_philo)
		return (1);
	return (0);
}

int	monitoring(t_params *data)
{
	int	i;
	int	flag;

	while (1)
	{
		flag = 1;
		i = 0;
		while (i < data->num_of_philo)
		{
			if (data->philos[i].max_eatings == -1 || data->philos[i].cnt_eatings < data->philos[i].max_eatings)
				flag = 0;
			if (is_dead(&data->philos[i]))
			{
				print_log(&data->philos[i], "died");
				return (1);
			}
			i++;
		}
		if (flag)
			return (0);
		// upd_usleep(500);
	}
}