/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouhami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:50:18 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/02 18:50:20 by atouhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_args
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				status;
	pthread_mutex_t	print;
	unsigned int	g_time;
	int				nbeats;
}	t_args;

typedef struct s_philo
{
	int					id;
	pthread_t			t_id;
	pthread_mutex_t		fork;
	pthread_mutex_t		*next_fork;
	t_args				*args;
	int					philosopher_eat_max;
	unsigned int		should_die;
}	t_philo;

/***** philo utils *****/
int					ft_atoi(const char *str);
int					take_input(int argc, char *argv[], t_args *args);
unsigned int		get_time(void);
void				ft_put_str(char *s, int id, t_args *args);
void				*health_check(void *philo);
#endif
