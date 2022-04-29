#include "philo.h"

long	get_time_ms(void)
{
	t_timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}

void    garbage_collector(t_params *data)
{
    if (data->forks)
        free(data->forks);
    if (data->philos)
        free(data->philos);
    free(data);
}