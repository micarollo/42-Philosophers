/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:28:45 by mrollo            #+#    #+#             */
/*   Updated: 2022/09/21 18:53:20 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_short_time(t_data *data)
{
	long long	time;

	time = get_time();
	// printf("now: %lld\n", time);
	return (time - data->time);
}

int	init_mutex(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (1);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	return (0);
}

void	create_philos(t_data *data)
{
	int i;

	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return ;
	i = 0;
	while (i <= data->n_philo)
	{
		data->philo[i].n = i + 1; //desde el 1 en adelante
		data->philo[i].born_time = get_time();
		data->philo[i].last_eat = 0;
		data->philo[i].fork_left = i + 1;
		data->philo[i].fork_right = i;
		// data->philo[i].is_dead = 0;
		i++;
	}
	data->philo[i - 1].fork_left = 0;
	
	//PRINT PHILOS
	// i = 0;
	// while (i <= data->n_philo)
	// {
	// 	printf("philo[%d] num: %d\n", i, data->philo[i].n);
	// 	printf("data->philo[%d].born_time %d\n", i, data->philo[i].born_time);
	// 	printf("philo[%d] fork_right: %d\n", i, data->philo[i].fork_right);
	// 	printf("philo[%d] fork_left: %i\n", i, data->philo[i].fork_left);
	// 	i++;
	// }
}

int	init_data(char **argv, t_data *data)
{
	data->n_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->are_alive = 1;
	if (argv[5])
		data->time_must_eat = atoi(argv[5]);
	create_philos(data);
	init_mutex(data);
	return (0);
}

int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5)
		write(2, "Argument missing\n", 17);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		init_data(argv, data);

		//PRUEBAS
		// data->time = get_time();
		// usleep(5000);
		// data->short_time = get_short_time(data);
		// printf("time: %lld\n", data->time);
		// printf("short_time: %ld\n", data->short_time);

		game(data);
	}
}