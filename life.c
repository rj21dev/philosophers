#include "philo.h"

void print_log(t_philo *philo, char *log)
{
    long    cur_time;

    int		test = 1;
	test = strcmp(log, "died");
	cur_time = get_tm();
	pthread_mutex_lock(philo->output);
    printf("%ld %d %s\n", cur_time, philo->philo_id, log);
	if (!test)
		return;
	pthread_mutex_unlock(philo->dead);
}

static void	is_thinking(t_philo *philo)
{
	print_log(philo, "is thinking");
}

static void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_1);
    print_log(philo, "has taken a fork");
    pthread_mutex_lock(philo->fork_2);
    print_log(philo, "has taken a fork");
    print_log(philo, "is eating");
    upd_usleep(philo->time_to_eat * 1000);
    pthread_mutex_lock(philo->synchro);
    philo->cnt_eatings++;
	philo->last_eat_tm = get_tm();
    pthread_mutex_unlock(philo->synchro);
    pthread_mutex_unlock(philo->fork_2);
    pthread_mutex_unlock(philo->fork_1);
}

static void	is_sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping");
	upd_usleep(philo->time_to_sleep * 1000);
}

void    *life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
	{
		is_thinking(philo);
		is_eating(philo);
		is_sleeping(philo);
		pthread_mutex_lock(philo->dead);
		if (!*philo->alive)
		{
			pthread_mutex_unlock(philo->dead);
			return (NULL);
		}
		pthread_mutex_unlock(philo->dead);
	}
	return (NULL);
}