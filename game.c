#include "philo.h"

void	print_action(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->data->write);
	if (n == 0)
		printf("%d is thinking\n", philo->n);
	if (n == 1)
		printf("%d has taken a fork\n", philo->n);
	if (n == 2)
		printf("%d is eating\n", philo->n);
	if (n == 3)
		printf("%d is sleeping\n", philo->n);
	if (n == 4)
		printf("%d is dead\n", philo->n);
	pthread_mutex_unlock(&philo->data->write);
}

void	*play(void *arg)
{
	t_philo	*philo;

	philo = arg;
	write(1, "s\n", 2);
	printf("philo: %d\n", philo->n);
	if (philo->n % 2)
		usleep(1500);
	while (1)
	{
		write(1, "t\n", 2);
		// print_action(philo, 0);
		// pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
		// print_action(philo, 1);
		// pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
		// print_action(philo, 1);
		// print_action(philo, 2);
		// philo->n_eats++;
		// philo->last_eat = get_short_time(philo->data);
		// pthread_mutex_unlock(&philo->data->forks[philo->fork_left]);
		// pthread_mutex_unlock(&philo->data->forks[philo->fork_right]);
		// print_action(philo, 3);
	}
	return (NULL);
}

int	is_anybody_dead(t_data *data)
{
	int	i;

	i = 0;
	while (data->are_alive)
	{
		while (i < data->n_philo)
		{
			// if (data->philo[i].is_dead == 1)
			if ((get_short_time(data) - data->philo[i].last_eat) > data->time_to_eat)
			{
				data->are_alive = 0;
				usleep(50);
				return (1);
			}
			i++;
		}
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
	while (i < data->n_philo)
	{
		write(1, "r\n", 2);
		if (pthread_create(&phi[i], NULL, play, &data->philo[i]))
			printf("error\n");
		i++;
	}
	is_anybody_dead(data);
	while (i > 0)
	{
		pthread_join(phi[i], NULL);
		i--;
	}
	return (0);
}