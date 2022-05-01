#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t	lock;
int	g_count = 0;

void	*thread_start(void *ptr)
{
	int	count_to;

	count_to = *(int *)ptr;

	for (int i = 0; i < count_to; i++)
	{
		pthread_mutex_lock(&lock);
		g_count++;
		pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <count_to> <thread_count>\n", argv[0]);
		return (1);
	}

	const int	count_to = atoi(argv[1]);
	if (count_to == 0)
	{
		printf("Valid 'count_to' is required.\n");
		return (1);
	}

	const int	thread_count = atoi(argv[2]);
	if (thread_count == 0)
	{
		printf("Valid 'thread_count' is required.\n");
		return (1);
	}

	pthread_t	tid[thread_count];
	for (int i = 0; i < thread_count; i++)
		pthread_create(&tid[i], NULL, thread_start, (void *)&count_to);

	for (int i = 0; i < thread_count; i++)
		pthread_join(tid[i], NULL);

	printf("Final result: %d\n", g_count);
	return (0);
}
