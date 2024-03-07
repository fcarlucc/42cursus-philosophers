/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:18:48 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/22 11:25:07 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (pthread_create(&philo->thread, NULL, &check_death, (void *)philo) != 0)
	{
		error("ERROR WHILE CREATING THREADS", philo->data, 0);
		return ((void *)1);
	}
	pthread_detach(philo->thread);
	while (philo->data->dead == 0 && philo->data->finished == 0)
	{
		eat(philo);
		if (philo->data->finished)
			break ;
		message("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep);
		if (philo->data->finished)
			break ;
		message("is thinking", philo);
	}
	ft_exit(philo->data);
	exit(0);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->dead == 0 && philo->data->finished == 0)
	{
		check_meals(philo);
		sem_wait(philo->lock);
		if ((get_time() >= philo->life_time) && philo->eating == 0)
		{
			sem_post(philo->lock);
			sem_wait(philo->data->lock);
			sem_wait(philo->data->write);
			printf("%llu %d %s\n", (get_time() - philo->data->start), \
			philo->id + 1, "is died");
			philo->data->dead = 1;
			exit(1);
			sem_post(philo->data->write);
			sem_post(philo->data->lock);
			break ;
		}
		sem_post(philo->lock);
	}
	return (NULL);
}

void	check_meals(t_philo *philo)
{
	sem_wait(philo->lock);
	sem_wait(philo->data->lock);
	if (philo->data->times_to_eat != -1)
		if (philo->meals == philo->data->times_to_eat)
			philo->data->finished = 1;
	sem_post(philo->lock);
	sem_post(philo->data->lock);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	message("has taken a fork", philo);
	sem_wait(philo->data->forks);
	message("has taken a fork", philo);
	sem_wait(philo->lock);
	sem_wait(philo->data->lock);
	philo->meals++;
	philo->eating = 1;
	philo->life_time = get_time() + philo->data->time_to_die;
	sem_post(philo->lock);
	sem_post(philo->data->lock);
	message("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	sem_wait(philo->lock);
	philo->eating = 0;
	sem_post(philo->lock);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	message(char *str, t_philo *philo)
{
	sem_wait(philo->data->write);
	printf("%llu %d %s\n", (get_time() - philo->data->start), \
	philo->id + 1, str);
	sem_post(philo->data->write);
}
