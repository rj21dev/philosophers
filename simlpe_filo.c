#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

pthread_mutex_t	forks[N];

void	*life(void *ptr)
{
	int id = *((int *)ptr);

	int left_fork = id;
	int right_fork = (id + 1) % N;
	
	int eatings = 0;
	while (eatings < 3)
	{
		printf("%d is thinking...\n", id);
		pthread_mutex_lock(&forks[left_fork]);
		printf("%d take a left fork (%d).\n", id, left_fork);
		pthread_mutex_lock(&forks[right_fork]);
		printf("%d take a right fork (%d).\n", id, right_fork);
		printf("%d is eating... %d times\n", id, eatings + 1);
		usleep(1000000);
		pthread_mutex_unlock(&forks[right_fork]);
		pthread_mutex_unlock(&forks[left_fork]);
		eatings++;
		printf("%d is sleeping...\n", id);
		usleep(1000000);
	}
	return (NULL);
}

int	main(void)
{
	for (int i = 0; i < N; i++)
		pthread_mutex_init(&forks[i], NULL);

	pthread_t tid[N];
	for (int i = 0; i < N; i++)
	{
		int *id = malloc(sizeof(int));
		*id = i;
		pthread_create(&tid[i], NULL, life, id);
	}

	for (int i = 0; i < N; i++)
		pthread_join(tid[i], NULL);

	for (int i = 0; i < N; i++)
		pthread_mutex_destroy(&forks[i]);

	return (0);
}
