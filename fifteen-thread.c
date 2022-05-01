#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

const int	num_threads = 15;

void	*thread_start(void *ptr)
{
	int	id;

	//usleep(1000000);
	id = *(int *)ptr;
	printf("Thread %d running...\n", id);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	tid[num_threads];

	for (int i = 0; i < num_threads; i++)
	{
		int *val = malloc(sizeof(int));
		*val = i;
		pthread_create(&tid[i], NULL, thread_start, val);
		//pthread_join(tid[i], NULL);
		//pthread_detach(tid[i]);
		free(val);
	}

	for (int i = 0; i < num_threads; i++)
		pthread_join(tid[i], NULL);

	//usleep(3000000);
	printf("Done\n");
	return (0);
}
