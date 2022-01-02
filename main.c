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
		args -> must_eat = 0;
	args -> nb_philo = ft_atoi(argv[1]);
	args -> time_die = ft_atoi(argv[2]);
	args -> time_eat = ft_atoi(argv[3]);
	args -> time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args -> must_eat = ft_atoi(argv[5]);
	if (args -> nb_philo == 0 || args -> time_die == 0 || args -> time_eat == 0 || args -> time_sleep == 0)
		return(printf("Wrong Arguments\n"),1);
	return 0;
}

int main(int argc, char *argv[])
{
	t_args args;

	if (take_input(argc, argv, &args) == 1)
		return 0;

	printf("%d %d %d %d %d", args.nb_philo, args.time_die, args.time_eat, args.time_sleep, args.must_eat);
}
