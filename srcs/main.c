/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:03:22 by rjada             #+#    #+#             */
/*   Updated: 2022/05/08 02:41:12 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	garbage_collector(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		free(data->philos[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
	free(data);
}

static int	is_valid_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philos [number_of_philos] [time_to_die] "
			"[time_to_eat] [time_to_sleep] ([times_each_philo_must_eat])\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[1]) > 200)
		{
			printf("Invalid argument.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (!is_valid_args(argc, argv))
		return (1);
	data = init_data(argv);
	if (!data)
		return (1);
	if (!init_threads(data))
		return (1);
	monitor(data);
	garbage_collector(data);
	return (0);
}
