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
	args -> nb_philo = ft_atoi(argv[1]);
	args -> time_die = ft_atoi(argv[2]);
	args -> time_eat = ft_atoi(argv[3]) * 1000;
	args -> time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		args -> must_eat = ft_atoi(argv[5]);
	if (args -> nb_philo <= 0 || args -> time_die <= 0 || args -> time_eat <= 0 || args -> time_sleep <= 0  || args->must_eat <= 0)
		return(printf("Wrong Arguments\n"),1);
	if (argc == 5)
		args -> must_eat = 0;
	return 0;
}

unsigned int get_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_put_str(char *s,int id, t_args *args, int died)
{
	pthread_mutex_lock(&args->print);
	printf("[%u] Philosopher %d %s\n",get_time(), id, s);
	if (!died)
		pthread_mutex_unlock(&args->print);
}

void *health_check(void* philo)
{
	t_philo *philosopher = (t_philo *)philo;
	while (1)
	{
		if (get_time() > philosopher->should_die + 10)
		{
			ft_put_str("is dead", philosopher->id, philosopher->args, 1);
			philosopher->args->status = 1;
		}
		else if (philosopher->good == 1) {
			philosopher->args->nbEats++;
			break;
		}
	}
	return (NULL);
}

void *philosophers(void *philo)
{
	int i;
	t_philo *philosopher = (t_philo *)philo;
	pthread_t thread_id;

	philosopher->good = 0;
	i = 0;
	philosopher->should_die = philosopher->args->g_time + philosopher->args->time_die;
	pthread_create(&thread_id,NULL, &health_check, philosopher);
	pthread_detach(thread_id);
	while (i < philosopher->args->must_eat || !(philosopher -> args -> must_eat))
	{
		ft_put_str("is thinking",philosopher->id, philosopher->args, 0);
		pthread_mutex_lock(&philosopher -> fork);
		ft_put_str("Has taken a fork",philosopher->id, philosopher->args, 0);
		pthread_mutex_lock(philosopher -> next_fork);
		ft_put_str("Has taken a fork",philosopher->id, philosopher->args, 0);
		philosopher->should_die = get_time() + philosopher->args->time_die;
		ft_put_str("is Eating",philosopher->id, philosopher->args, 0);
		usleep(philosopher->args->time_eat);
		pthread_mutex_unlock(&philosopher -> fork);
		pthread_mutex_unlock(philosopher -> next_fork);
		usleep(philosopher->args->time_sleep);
		i++;
		if (i == philosopher->args->must_eat)
			ft_put_str("is thinking",philosopher->id, philosopher->args, 0);
	}
	philosopher->good = 1;
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
			pthread_mutex_init(&philo[i++].fork, NULL);
	i = 0;
	while(i < args -> nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].args = args;
		if (i == args->nb_philo - 1)
			philo[i].next_fork = &philo[0].fork;
		else
			philo[i].next_fork = &philo[i + 1].fork;
		i++;
	}
	i = 0;
	args->g_time = get_time();
	while(i < args -> nb_philo)
	{
		if (pthread_create(&philo[i].t_id,NULL, &philosophers,&philo[i]))
			return(printf("Error occured thread creation"), 1);
		usleep(100);
		i++;
	}
	i = 0;
	while(i < args -> nb_philo)
		pthread_detach(philo[i++].t_id);
	return 0;
}

int main(int argc, char *argv[])
{
	t_args args;

	args.status = 0;
	args.nbEats = 0;
	pthread_mutex_init(&args.print, NULL);
	if (take_input(argc, argv, &args) == 1)
		return (0);
	if (ft_create_philosophers(&args) == 1)
		return (0);
	while (args.status == 0) {
		if (args.nbEats == args.nb_philo)
			break ;
		usleep(10);
	}
	return 0;
}
