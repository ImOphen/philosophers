/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouhami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:49:50 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/02 18:49:54 by atouhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers_activities(t_philo *philosopher)
{
	ft_put_str("is thinking", philosopher->id, philosopher->args, 0);
	pthread_mutex_lock(&philosopher -> fork);
	ft_put_str("has taken a fork", philosopher->id, philosopher->args, 0);
	pthread_mutex_lock(philosopher -> next_fork);
	ft_put_str("has taken a fork", philosopher->id, philosopher->args, 0);
	philosopher->should_die = get_time() + philosopher->args->time_die;
	ft_put_str("is eating", philosopher->id, philosopher->args, 0);
	usleep(philosopher->args->time_eat);
	pthread_mutex_unlock(&philosopher -> fork);
	pthread_mutex_unlock(philosopher -> next_fork);
	ft_put_str("is sleeping", philosopher->id, philosopher->args, 0);
	usleep(philosopher->args->time_sleep);
}

void	*philosophers(void *philo)
{
	int			i;
	t_philo		*philosopher;
	pthread_t	thread_id;

	philosopher = (t_philo *)philo;
	philosopher->philosopher_eat_max = 0;
	i = 0;
	philosopher->should_die = philosopher->args->g_time
		+ philosopher->args->time_die;
	pthread_create(&thread_id, NULL, &health_check, philosopher);
	pthread_detach(thread_id);
	while (i < philosopher->args->must_eat
		|| !(philosopher -> args -> must_eat))
	{
		philosophers_activities(philosopher);
		i++;
		if (i == philosopher->args->must_eat)
			ft_put_str("is thinking", philosopher->id, philosopher->args, 0);
	}
	philosopher->philosopher_eat_max = 1;
	return (NULL);
}

void	fill_philo(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args -> nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].args = args;
		if (i == args->nb_philo - 1)
			philo[i].next_fork = &philo[0].fork;
		else
			philo[i].next_fork = &philo[i + 1].fork;
		i++;
	}
}

t_philo	*ft_create_philosophers(t_args *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * args -> nb_philo);
	if (!philo)
		return (printf("Error occured during allocation"), NULL);
	while (i < args -> nb_philo)
		pthread_mutex_init(&philo[i++].fork, NULL);
	i = 0;
	fill_philo(philo, args);
	args->g_time = get_time();
	while (i < args -> nb_philo)
	{
		if (pthread_create(&philo[i].t_id, NULL, &philosophers, &philo[i]))
			return (free(philo), printf("Error occured thread creation"), NULL);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < args -> nb_philo)
		pthread_detach(philo[i++].t_id);
	return (philo);
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philo;
	int		i;

	args.status = 0;
	args.nbeats = 0;
	if (take_input(argc, argv, &args) == 1)
		return (0);
	pthread_mutex_init(&args.print, NULL);
	philo = ft_create_philosophers(&args);
	if (philo == NULL)
		return (0);
	while (args.status == 0)
	{
		if (args.nbeats == args.nb_philo)
			break ;
		usleep(10);
	}
	i = 0;
	while (i < args.nb_philo)
		pthread_mutex_destroy(&philo[i++].fork);
	pthread_mutex_destroy(&args.print);
	free(philo);
	return (0);
}
