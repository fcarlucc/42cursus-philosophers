/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:59:52 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/21 20:00:51 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				meals;
	int				eating;
	u_int64_t		life_time;
	sem_t			*lock;
}		t_philo;

typedef struct s_data
{
	int				n_philos;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				times_to_eat;
	int				dead;
	int				finished;
	u_int64_t		start;
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*lock;
	sem_t			*write;
	t_philo			*philo;
}		t_data;

int			init(int ac, char **av, t_data *data);
int			init_table(t_data *data);
void		init_processes(t_data *data);
void		*routine(void *arg);
void		*check_death(void *arg);
void		check_meals(t_philo *philo);
void		eat(t_philo *philo);
void		message(char *str, t_philo *philo);
u_int64_t	get_time(void);
int			error(char *str, t_data *data, int flag);
int			ft_usleep(u_int64_t time);
void		ft_exit(t_data *data);
int			check_args(const char *str);

#endif