#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define MSG "Usage: ./philos [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([times_each_philosopher_must_eat])\n"
# define EATING 1
# define TAKE_FORK 2
# define SLEEPING 3

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;

typedef struct	s_philo
{
	int         philo_id;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         max_eatings;
	int			cnt_eatings;
    long        last_eat_tm;
	int			*alive;
    pthread_t   life_tid;
    t_mutex	    *output;
    t_mutex     *synchro;
	t_mutex		*dead;
    t_mutex	    *fork_1;
    t_mutex	    *fork_2;
}				t_philo;

typedef struct	s_params
{
	int		num_of_philo;
	int		alive;
	t_philo	*philos;
	t_mutex	*forks;
	t_mutex	output;
    t_mutex synchro;
	t_mutex	dead;
}				t_params;

long	get_tm(void);
void 	print_log(t_philo *philo, char *log);
void 	upd_usleep(unsigned n);
void    garbage_collector(t_params *data);
int	    init_mutexes(t_params *data);
int	    kill_mutexes(t_params *data);
int     start_threads(t_params *data);
int	    join_threads(t_params *data);
void    *life(void *arg);
int		monitoring(t_params *data);

#endif