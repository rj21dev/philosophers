#include "philo.h"

static void print_log(t_philo *philo, int state, char *log)
{
    long    cur_time;

    if (!*philo->is_alive)
        return ;
    pthread_mutex_lock(philo->output);
    cur_time = get_time_ms();
    if (state == EATING)
        philo->last_eat_tm = cur_time;
    else if (state == TAKE_FORK)
    {
        if (!philo->first_hand)
            ++philo->first_hand;
        else
            ++philo->second_hand;
    }
    else if (state == SLEEPING)
    {
        philo->first_hand = 0;
        philo->second_hand = 0;
    }
    if (*philo->is_alive)
        printf("%ld %d %s\n", cur_time, philo->philo_id, log);
    pthread_mutex_unlock(philo->output);
}

static void upd_usleep(unsigned n)
{
    long    start;
    long    step;

    start = get_time_ms();
    while (1)
    {
        step = get_time_ms();
        if ((step - start) * 1000 >= n)
            break ;
        usleep(500);
    }
}

void    *life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (*philo->is_alive && philo->max_eatings != 0)
    {
        --philo->max_eatings;
        print_log(philo, 0, "is thinking");
        pthread_mutex_lock(philo->fork_1);
        print_log(philo, TAKE_FORK, "has taken a fork");
        pthread_mutex_lock(philo->fork_2);
        print_log(philo, TAKE_FORK, "has taken a fork");
        print_log(philo, EATING, "is eating");
        upd_usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(philo->fork_1);
        pthread_mutex_unlock(philo->fork_2);
        print_log(philo, SLEEPING, "is sleaping");
        upd_usleep(philo->time_to_sleep * 1000);
    }
    return (NULL);
}

void    *monitor(void *arg)
{
    long    cur_time;
    t_philo *philo;

    philo = (t_philo *)arg;
    while (*philo->is_alive && philo->max_eatings != 0)
    {
        cur_time = get_time_ms();
        if (cur_time - philo->last_eat_tm > philo->time_to_die)
        {
            print_log(philo, 0, "died");
            *philo->is_alive = 0;
            break ;
        }
        upd_usleep(500);
    }
    if (philo->first_hand)
        pthread_mutex_unlock(philo->fork_1);
    if (philo->second_hand)
        pthread_mutex_unlock(philo->fork_2);
    return (NULL);
}

long	get_time_ms(void)
{
	t_timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}