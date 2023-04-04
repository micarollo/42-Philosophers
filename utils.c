/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:12:03 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/04 17:57:44 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
    free (data->philo);
    free (data->forks);
	pthread_mutex_destroy(&data->write);
    pthread_mutex_destroy(&data->death);
	free(data);
}

long long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	ft_clean_atoi(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == '\t')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				n;
	unsigned int	result;

	n = 1;
	result = 0;
	i = ft_clean_atoi(nptr);
	if (nptr[i] == '-')
	{
		n = n * -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		if (result > 2147483647 && n == 1)
			return (-1);
		if (result > 2147483648 && n == -1)
			return (0);
		i++;
	}
	return (result * n);
}