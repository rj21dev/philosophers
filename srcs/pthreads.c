#include "philo.h"

int	init_mutexes(t_params *data)
{
	int	i;

	i = 0;
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * data->num_of_philo);
	if (!data->forks)
	{
		printf("Malloc error\n");
		return (0);
	}
	while (i < data->num_of_philo)
	{
		if(pthread_mutex_init(data->forks + i, NULL))
		{
			printf("Mutex init error\n");
			return (0);
		}
		i++;
	}
	if(pthread_mutex_init(&data->output, NULL))
	{
			printf("Mutex init error\n");
			return (0);
	}
	pthread_mutex_init(&data->lock_eatings, NULL);
	pthread_mutex_init(&data->lock_alive, NULL);
	return (1);
}

int	kill_mutexes(t_params *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			return (0);
		i++;
	}
	return (1);
}

int start_threads(t_params *data)
{
    int i;
	int	error;

    i = 0;
    while (i < data->num_of_philo)
    {
        error = pthread_create(&data->philos[i].life_tid, NULL, life, &data->philos[i]);
		if (error)
			return (0);
        error = pthread_create(&data->philos[i].scan_tid, NULL, monitor, &data->philos[i]);
		if (error)
			return (0);
        i++;
    }
    return (1);
}

int	join_threads(t_params *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philos[i].life_tid, NULL);
		pthread_join(data->philos[i].scan_tid, NULL);
		i++;
	}
	return (1);
}

void    garbage_collector(t_params *data)
{
    if (data->forks)
        free(data->forks);
    if (data->philos)
        free(data->philos);
    free(data);
}