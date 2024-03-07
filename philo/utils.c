/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:14:53 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/21 19:46:37 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (error("gettimeofday() HA FALLITO\n", NULL, 0));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	error(char *str, t_data *data, int flag)
{
	if (str != NULL)
		printf("%s\n", str);
	if (flag == 1)
	{
		write(2, "ARG ERROR\n", 10);
		return (-2);
	}
	if (data)
		ft_exit(data);
	return (1);
}

void	clear_data(t_data	*data)
{
	if (data->td)
		free(data->td);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}
