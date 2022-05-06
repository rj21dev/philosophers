#include "philo.h"

void upd_usleep(unsigned n)
{
    long    start;
    long    step;

    start = get_tm();
    while (1)
    {
        step = get_tm();
        if ((step - start) * 1000 >= n)
            break ;
        usleep(500);
    }
}

long	get_tm(void)
{
	t_timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}