/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:02:55 by rjada             #+#    #+#             */
/*   Updated: 2022/05/08 02:41:39 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_mutex	*mutexes_init(t_data *data)
{
	t_mutex	*forks;
	int		i;

	forks = malloc(sizeof(t_mutex) * data->philo_num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	mutexes_kill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->forks = mutexes_init(data);
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	pthread_mutex_init(&data->prnt, NULL);
	if (argv[5])
		data->max_eatings = ft_atoi(argv[5]);
	else
		data->max_eatings = -1;
	return (data);
}

static t_philo	*init_philo(int i, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->data = data;
	philo->eat_count = data->max_eatings;
	philo->fork_2 = i;
	philo->fork_1 = (i + data->philo_num - 1) % data->philo_num;
	if (i == 0)
	{
		philo->fork_2 = (i + data->philo_num - 1) % data->philo_num;
		philo->fork_1 = 0;
	}
	pthread_mutex_init(&philo->swap, NULL);
	philo->last_eat_tm = get_tm();
	return (philo);
}

int	init_threads(t_data *data)
{
	t_philo		*philo;
	pthread_t	tid;
	int			i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	while (i < data->philo_num)
	{
		philo = init_philo(i, data);
		data->philos[i] = philo;
		if (pthread_create(&tid, NULL, life, philo))
			return (0);
		pthread_detach(tid);
		i++;
	}
	return (1);
}
