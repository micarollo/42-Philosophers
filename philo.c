/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:28:45 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/03 20:10:08 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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
		data->philo[i].last_eat = get_time();
		data->philo[i].fork_left = i + 1;
		data->philo[i].fork_right = i;
		data->philo[i].data = data;
		i++;
	}
	data->philo[i - 1].fork_left = 0;
}

int	check_arg(char *str)
{
	while (*str)
	{
		if (*str < 48 || *str > 59)
			return (1);
		str++;
	}
	return (0);
}

int	init_data(char **argv, t_data *data)
{
	if (check_arg(argv[1]) || check_arg(argv[2]) || check_arg(argv[3]) || check_arg(argv[4]))
		return (1);
	data->n_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->are_alive = 1;
	data->time = get_time();
	if (argv[5])
		data->meals = atoi(argv[5]);
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
		if (init_data(argv, data))
		{
			printf("argument error\n");
			return (1);
		}
		init_mutex(data);	
		create_philos(data);
		game(data);
	}
	return (0);
}