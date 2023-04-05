/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:25:07 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/05 13:48:51 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->are_alive && !philo->data->full)
	{
		if (n == 0)
			printf("[%lld] %d is thinking\n", (get_time() - philo->data->time), philo->n);
		if (n == 1)
			printf("[%lld] %d has taken a fork\n", (get_time() - philo->data->time), philo->n);
		if (n == 2)
			printf("[%lld] %d is eating\n", (get_time() - philo->data->time), philo->n);
		if (n == 3)
			printf("[%lld] %d is sleeping\n", (get_time() - philo->data->time), philo->n);
		if (n == 4)
			printf("[%lld] %d is dead\n", (get_time() - philo->data->time), philo->n);
	}
	pthread_mutex_unlock(&philo->data->write);
}

void	*play(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->n % 2 == 0)
		usleep(1500);
	while (philo->data->are_alive && !philo->data->full)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	is_anybody_dead(t_data *data)
{
	int	i;

	while (data->are_alive && !data->full)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->death);
			if (((get_time() - data->time) - data->philo[i].last_eat ) >= data->time_to_die)
			{
				print_action(&data->philo[i], 4);
				data->are_alive = 0;
				// usleep(50);
				return (1);
			}
			pthread_mutex_unlock(&data->death);
			i++;
		}
		i = 0;
		while(data->meals && i < data->n_philo)
		{
			if (data->philo[i].n_eats >= data->meals)
			{
				if (i == (data->n_philo - 1))
				{
					data->full = 1;
					return (1);
				}
			}
			else
				break ;
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
		if (pthread_create(&phi[i], NULL, play, &data->philo[i]))
			printf("error\n");
		i++;
	}
	is_anybody_dead(data);
	while (i > 0)
	{
		if (pthread_join(phi[i], NULL))
			return (1);
		i--;
	}
	if (phi)
		free (phi);
	return (0);
}