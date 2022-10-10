/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:31:06 by mrollo            #+#    #+#             */
/*   Updated: 2022/09/21 18:52:36 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int n;
	int born_time;
	int last_eat;
	int fork_left;
	int fork_right;
}		t_philo;

typedef struct	s_data
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	//int	time_must_eat;
	t_philo	*philo;
	long long	time;
	long	short_time;
}		t_data;

#endif