/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:03:14 by rjada             #+#    #+#             */
/*   Updated: 2022/05/08 02:29:13 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eatings;
	t_mutex			prnt;
	t_mutex			*forks;
	t_philo			**philos;
}				t_data;

struct	s_philo
{
	int				id;
	int				fork_1;
	int				fork_2;
	long			last_eat_tm;
	int				eat_count;
	t_mutex			swap;
	t_data			*data;
};

int				ft_atoi(const char *str);
int				init_threads(t_data *data);
long			get_tm(void);
void			upd_usleep(long delay);
void			*life(void *arg);
void			monitor(t_data *data);
void			print_log(t_philo *philo, const char *msg);
void			mutexes_kill(t_data *data);
t_data			*init_data(char **argv);

#endif
