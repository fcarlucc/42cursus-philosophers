/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:51:35 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/07/14 20:56:34 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		life_cycle(philo);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->dead == 0 && philo->data->finished == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if ((get_time() >= philo->life_time) && philo->eating == 0)
		{
			pthread_mutex_unlock(&philo->lock);
			pthread_mutex_lock(&philo->data->lock);
			pthread_mutex_lock(&philo->data->write);
			printf("%llu %d %s\n", (get_time() - philo->data->start), \
			philo->id + 1, "is died");
			philo->data->dead = 1;
			ft_usleep(10000);
			pthread_mutex_unlock(&philo->data->write);
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*check_meals(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (data->dead == 0 && data->finished == 0)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (data->philo[i].meals < data->times_to_eat)
				break ;
			i++;
		}
		if (i == data->n_philos)
		{
			pthread_mutex_lock(&data->lock);
			data->finished = 1;
			ft_usleep(100);
			pthread_mutex_unlock(&data->lock);
		}
	}
	return (NULL);
}

void	life_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->left);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
	philo->meals++;
	philo->eating = 1;
	philo->life_time = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	message("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	message("is thinking", philo);
}

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d %s\n", (get_time() - philo->data->start), \
	philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->write);
}
