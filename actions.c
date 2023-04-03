/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:03:10 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/03 19:34:20 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
	print_action(philo, 1);
	print_action(philo, 2);
	philo->n_eats++;
	philo->last_eat = get_time() - philo->data->time;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_right]);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_action(philo, 0);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_action(philo, 3);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

long	ft_usleep(int time)
{
	long long	now;

	now = get_time();
	while (time > (get_time() - now))
	{
		if (usleep(1) == -1)
		{
			printf("error\n");
			return (1);
		}
	}
	return (0);
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		free(&data->philo[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	free(data);
}