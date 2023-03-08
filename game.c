#include "philo.h"

void	*play(void *arg)
{
	t_philo	*philo;

	philo = arg;
}

int	is_anybody_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->n_philo)
	{
		if (data->philo[i].is_dead == 1)
			return (1);
		i++;
	}
	return (0);
}

int	game(t_data *data)
{
	pthread_t	*phi;
	int	i;

	phi = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philo);
	if (!phi)
		return (1);
	i = 0;
	while (i <= data->n_philo)
	{
		pthread_create(&phi[i], NULL, play, &data->philo[i]);
	}
	is_anybody_dead(data);
}