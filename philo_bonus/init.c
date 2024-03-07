/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:55:06 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/21 19:59:15 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_table(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].meals = 0;
		data->philo[i].eating = 0;
		data->philo[i].life_time = get_time() + data->time_to_die;
		sem_unlink("/LOCK");
		data->philo[i].lock = sem_open("/LOCK", O_CREAT, 0644, 1);
		if (data->philo[i].lock == SEM_FAILED)
			return (0);
	}
	sem_unlink("/FORKS");
	data->forks = sem_open("/FORKS", O_CREAT, 0644, data->n_philos);
	if (data->forks == SEM_FAILED)
		return (0);
	return (1);
}

int	init(int ac, char **av, t_data *data)
{
	data->n_philos = check_args(av[1]);
	data->time_to_die = check_args(av[2]);
	data->time_to_eat = check_args(av[3]);
	data->time_to_sleep = check_args(av[4]);
	if (ac == 6)
		data->times_to_eat = check_args(av[5]);
	else
		data->times_to_eat = -1;
	if (data->n_philos < 1 || data->n_philos > 200 || data->time_to_die < 0 || \
	data->time_to_eat < 0 || data->time_to_sleep < 0 || data->times_to_eat < -1)
		return (0);
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	data->time_to_die = (u_int64_t)data->time_to_die;
	data->time_to_eat = (u_int64_t)data->time_to_eat;
	data->time_to_sleep = (u_int64_t)data->time_to_sleep;
	data->dead = 0;
	data->finished = 0;
	data->start = get_time();
	sem_unlink("/WRITE");
	data->write = sem_open("/WRITE", O_CREAT, 0644, 1);
	sem_unlink("/LOCK");
	data->lock = sem_open("/LOCK", O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED || data->lock == SEM_FAILED)
		return (0);
	return (1);
}

void	init_processes(t_data *data)
{
	int		i;
	int		status;

	i = -1;
	status = 0;
	data->pid = (int *)malloc(sizeof(int) * data->n_philos);
	while (++i < data->n_philos)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			routine(&data->philo[i]);
	}
	waitpid(-1, &status, 0);
	i = -1;
	if (WEXITSTATUS(status) == 0 && data->times_to_eat > 0)
	{
		while (++i < data->n_philos && WEXITSTATUS(status) == 0)
			waitpid(data->pid[i], &status, 0);
	}
	i = -1;
	while (++i < data->n_philos)
		kill(data->pid[i], SIGTERM);
	ft_exit(data);
}
