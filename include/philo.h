/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:31:06 by mrollo            #+#    #+#             */
/*   Updated: 2023/04/05 16:30:31 by mrollo           ###   ########.fr       */
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
	int				n;
	int				born_time;
	int				last_eat;
	int				fork_left;
	int				fork_right;
	int				n_eats;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	long long		time;
	int				are_alive;
	int				full;
	t_philo			*philo;
}		t_data;

long long	get_time(void);
void		ft_usleep(int time);
int			game(t_data *data);
void		print_action(t_philo *philo, int n);
int			eating(t_philo *philo);
int			thinking(t_philo *philo);
int			sleeping(t_philo *philo);
int			ft_clean(t_data *data);
int			ft_atoi(const char *nptr);

#endif