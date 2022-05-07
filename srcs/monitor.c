/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:03:10 by rjada             #+#    #+#             */
/*   Updated: 2022/05/08 02:43:35 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_satisfied(t_data *data)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i]->swap);
		total += data->philos[i]->eat_count;
		pthread_mutex_unlock(&data->philos[i]->swap);
		i++;
	}
	if (!total)
		return (1);
	return (0);
}

static int	is_dead(t_data *data)
{
	int				i;
	long			last_dinner;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i]->swap);
		last_dinner = data->philos[i]->last_eat_tm;
		pthread_mutex_unlock(&data->philos[i]->swap);
		if (get_tm() - last_dinner >= data->time_to_die)
		{
			pthread_mutex_lock(&data->prnt);
			printf("%lu %d died\n", get_tm(), data->philos[i]->id);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor(t_data *data)
{
	while (1)
	{
		if (is_dead(data))
			break ;
		if (is_satisfied(data))
			break ;
		usleep(500);
	}
}
