/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouhami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:17:34 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/04 20:17:36 by atouhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	count;

	i = 0;
	sign = 1;
	count = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = count * 10 + str[i] - 48;
		i++;
	}
	return (count * sign);
}

int	take_input(int argc, char *argv[], t_args *args)
{
	if (argc != 6 && argc != 5)
		return (printf("Wrong Arguments\n"), 1);
	args -> must_eat = 1;
	args -> nb_philo = ft_atoi(argv[1]);
	args -> time_die = ft_atoi(argv[2]);
	args -> time_eat = ft_atoi(argv[3]) * 1000;
	args -> time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		args -> must_eat = ft_atoi(argv[5]);
	if (args -> nb_philo <= 0 || args -> time_die <= 0
		|| args -> time_eat <= 0 || args -> time_sleep <= 0
		|| args->must_eat <= 0)
		return (printf("Wrong Arguments\n"), 1);
	if (argc == 5)
		args -> must_eat = 0;
	return (0);
}

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_put_str(char *s, int id, t_args *args)
{
	pthread_mutex_lock(&args->print);
	printf("%u %d %s\n", get_time() - args->g_time, id, s);
	pthread_mutex_unlock(&args->print);
}

void	*health_check(void *philo)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philo;
	while (1)
	{
		if (get_time() > philosopher->should_die + 8)
		{
			ft_put_str("died", philosopher->id, philosopher->args);
			pthread_mutex_lock(&philosopher->args->print);
			philosopher->args->status = 1;
		}
		else if (philosopher->philosopher_eat_max == 1)
		{
			philosopher->args->nbeats++;
			break ;
		}
	}
	return (NULL);
}
