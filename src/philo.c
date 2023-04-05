/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:28:45 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/05 13:48:38 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

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
	pthread_mutex_init(&data->death, NULL);
	return (0);
}

void	create_philos(t_data *data)
{
	int i;

	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return ;
	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].n = i + 1;
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
	// cambiar x ft_strcmp
	// if (strcmp(str, "0") == 0)
	// 	return (1);
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
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->n_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	data->are_alive = 1;
	data->full = 0;
	data->time = get_time();
	data->meals = 0;
	if (argv[5] && !check_arg(argv[5]))
	{
		data->meals = ft_atoi(argv[5]);
		if (data->meals <= 0)
			return (1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5)
		printf("Argument missing\n");
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		if (init_data(argv, data))
		{
			printf("argument error\n");
			free (data);
			return (1);
		}
		init_mutex(data);	
		create_philos(data);
		game(data);
		ft_clean(data);
	}
	printf("f\n");
	system("leaks philo");
	return (0);
}