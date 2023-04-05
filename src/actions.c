/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:03:10 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/05 16:10:54 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
	print_action(philo, 1);
	if (philo->data->n_philo == 1)
	{
		ft_usleep(philo->data->time_to_die);
		print_action(philo, 4);
		philo->data->are_alive = 0;
		return (0);
	}
	pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->data->death);
	print_action(philo, 2);
	philo->n_eats++;
	philo->last_eat = get_time() - philo->data->time;
	pthread_mutex_unlock(&philo->data->death);
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

void	ft_usleep(int time)
{
	long long	now;

	now = get_time();
	while (1)
	{
		if ((get_time() - now) >= time)
			break ;
		usleep(100);
	}
}
