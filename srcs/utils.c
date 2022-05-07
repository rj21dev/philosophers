#include "philo.h"

int	check_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_alive);
	if (!*philo->is_alive)
	{
		pthread_mutex_unlock(philo->lock_alive);
		return (0);
	}
	pthread_mutex_unlock(philo->lock_alive);
	return (1);
}

static void print_log(t_philo *philo, char *log)
{
    long    cur_time;

	if (!check_alive(philo))
        return ;
    pthread_mutex_lock(philo->output);
    cur_time = get_time_ms();
    if (strcmp(log, "is eating") == 0)
    {
        pthread_mutex_lock(philo->lock_eatings);
        philo->last_eat_tm = cur_time;
        pthread_mutex_unlock(philo->lock_eatings);
    }
    if (check_alive(philo))
        printf("%ld %d %s\n", cur_time, philo->philo_id, log);
    pthread_mutex_unlock(philo->output);
}

void    *life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (!check_alive(philo))
			break;
        pthread_mutex_lock(philo->fork_1);
        print_log(philo, "has taken a fork");
        pthread_mutex_lock(philo->fork_2);
        print_log(philo, "has taken a fork");
        print_log(philo, "is eating");
        usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(philo->fork_1);
        pthread_mutex_unlock(philo->fork_2);
		pthread_mutex_lock(philo->lock_eatings);
        --philo->max_eatings;
        if (!philo->max_eatings)
        {
            pthread_mutex_unlock(philo->lock_eatings);
            break;
        }
        pthread_mutex_unlock(philo->lock_eatings);
        print_log(philo, "is sleaping");
        usleep(philo->time_to_sleep * 1000);
		print_log(philo, "is thinking");
    }
    return (NULL);
}

void    *monitor(void *arg)
{
    long    cur_time;
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(philo->lock_eatings);
        if (!philo->max_eatings)
        {
            pthread_mutex_unlock(philo->lock_eatings);
            break;
        }  
        cur_time = get_time_ms();
        if (cur_time - philo->last_eat_tm > philo->time_to_die)
        {
            pthread_mutex_unlock(philo->lock_eatings);
            print_log(philo, "died");
            pthread_mutex_lock(philo->lock_alive);
			*philo->is_alive = 0;
			pthread_mutex_unlock(philo->lock_alive);
            break ;
        }
        pthread_mutex_unlock(philo->lock_eatings);
    }
    return (NULL);
}

long	get_time_ms(void)
{
	t_timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}