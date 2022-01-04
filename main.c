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

int take_input(int argc,char *argv[], t_args *args)
{
	if (argc != 6 && argc != 5)
		return(printf("Wrong Arguments\n"),1);
	args -> must_eat = 1;
	args -> nb_philo = ft_atoi(argv[1]);
	args -> time_die = ft_atoi(argv[2]);
	args -> time_eat = ft_atoi(argv[3]);
	args -> time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args -> must_eat = ft_atoi(argv[5]);
	if (args -> nb_philo <= 0 || args -> time_die <= 0 || args -> time_eat <= 0 || args -> time_sleep <= 0)
		return(printf("Wrong Arguments\n"),1);
	return 0;
}

void ft_put_eat(int id)
{
	printf("Philosopher %d is eating\n", id + 1);
}

void ft_put_sleep(int id)
{
	printf("Philosopher %d is sleeping\n", id + 1);
}

void *philosophers(void *philo)
{
	int i;
	t_philo *philosopher = (t_philo *)philo;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&philosopher -> fork);
		pthread_mutex_lock(philosopher -> next_fork);
		while (i < philosopher->args->must_eat)
		{
			ft_put_eat(philosopher->id);
			usleep(philosopher->args->time_eat);
			i++;
		}
		pthread_mutex_unlock(&philosopher -> fork);
		pthread_mutex_unlock(philosopher -> next_fork);
		ft_put_sleep(philosopher->id);
		usleep(philosopher->args->time_sleep);
	}
	return NULL;
}

int ft_create_philosophers(t_args *args)
{
	t_philo *philo;
	int i;
	i = 0;
	philo = malloc(sizeof(t_philo) * args -> nb_philo);
	if (!philo)
		return(printf("Error occured during allocation"), 1);
	while(i < args -> nb_philo)
	{
			pthread_mutex_init(&philo[i].fork, NULL);
			i++;
	}
	i = 0;
	while(i < args -> nb_philo)
	{
		philo[i].id = i;
		philo[i].args = args;
		if (i == args->nb_philo - 1)
			philo[i].next_fork = &philo[0].fork;
		else
			philo[i].next_fork = &philo[i + 1].fork;
		if (pthread_create(&philo[i].t_id,NULL, &philosophers,&philo[i]))
			return(printf("Error occured thread creation"), 1);
		i++;
	}
	i = 0;
	while(i < args -> nb_philo)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	t_args args;

	if (take_input(argc, argv, &args) == 1)
		return (0);
	if (ft_create_philosophers(&args) == 1)
		return (0);
	//printf("%d %d %d %d %d", args.nb_philo, args.time_die, args.time_eat, args.time_sleep, args.must_eat);
}
