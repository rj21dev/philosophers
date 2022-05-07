/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:03:26 by rjada             #+#    #+#             */
/*   Updated: 2022/05/08 02:43:28 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_log(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->prnt);
	printf("%ld %d %s\n", get_tm(), philo->id, msg);
	pthread_mutex_unlock(&philo->data->prnt);
}

static void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_1]);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->fork_2]);
	print_log(philo, "has taken a fork");
	print_log(philo, "is_eating");
	upd_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->swap);
	if (philo->eat_count > 0)
		philo->eat_count--;
	philo->last_eat_tm = get_tm();
	pthread_mutex_unlock(&philo->swap);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_2]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_1]);
}

static void	is_sleeping(t_philo *philo)
{
	print_log(philo, "is_sleeping");
	upd_usleep(philo->data->time_to_sleep);
}

static void	is_thinking(t_philo *philo)
{
	print_log(philo, "is_thinking");
}

void	*life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->eat_count)
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
		usleep(500);
	}
	return (NULL);
}
