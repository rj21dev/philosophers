#include <pthread.h>
#include <stdio.h>

void	*test1(void *data)
{
	int i = (int)data;
	printf("%d Hello\n", i);
	return (NULL);
}

int	main(void)
{
	pthread_t	id;
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&id, NULL, test1, &i);
		// pthread_join(id, NULL);
		pthread_detach(id);
	}
	return (0);
}
