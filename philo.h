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

typedef struct s_args
{
	int nb_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int must_eat;
}	t_args;

typedef struct s_philo
{
	int id;
	pthread_t t_id;
	pthread_mutex_t fork;
	pthread_mutex_t *next_fork;
	t_args *args;
}	t_philo;

#endif
