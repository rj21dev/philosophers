#include "philo.h"

static void	init_forks(t_params *data, int i)
{
	if (data->philos[i].philo_id == data->num_of_philo)
	{
		data->philos[i].fork_1 = &data->forks[0];
		data->philos[i].fork_2 = &data->forks[i];
	}
	else
	{
		data->philos[i].fork_1 = &data->forks[i];
		data->philos[i].fork_2 = &data->forks[i + 1];
	}
}

static int	init_philos(char **argv, t_params *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].first_hand = 0;
		data->philos[i].second_hand = 0;
		data->philos[i].time_to_die = atoi(argv[2]); //libc
		data->philos[i].time_to_eat = atoi(argv[3]);
		data->philos[i].time_to_sleep = atoi(argv[4]);
		data->philos[i].max_eatings = -1;
		if (argv[5])
			data->philos[i].max_eatings = atoi(argv[5]);
		data->philos[i].is_alive = &data->is_alive;
		data->philos[i].last_eat_tm = get_time_ms();
		data->philos[i].output = &data->output;
		init_forks(data, i);
		i++;
	}
	return (1);
}

static int	is_valid_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf(MSG);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (atoi(argv[i]) <= 0) //libc
		{
			printf("Invalid argument.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static t_params	*init_params(int argc, char **argv, t_params *data)
{
    data = (t_params *)malloc(sizeof(t_params));
	if (!data)
	{
		printf("Malloc error\n");
		return (NULL);
	}
	memset(data, 0, sizeof(t_params));
	if (!is_valid_args(argc, argv) || !init_mutexes(data))
	{
		garbage_collector(data);
		return (NULL);
	}
	data->num_of_philo = atoi(argv[1]); //libc
	data->is_alive = 1;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philos)
	{
		printf("Malloc error\n");
		garbage_collector(data);
		return (NULL);
	}
	init_philos(argv, data);
    return (data);
}

int	main(int argc, char **argv)
{
	t_params	*data;

	data = NULL;
	data = init_params(argc, argv, data);
	if (!data)
		return (1);
	// if (!start_threads(data) || !join_threads(data) \
	// 			|| !kill_mutexes(data))
	// {
	// 	garbage_collector(data);
	// 	return (2);
	// }
	if (!start_threads(data))
		return 2;
	if (!join_threads(data))
		return 3;
	if (!kill_mutexes(data))
		return 4;
	garbage_collector(data);
	return (0);
}
