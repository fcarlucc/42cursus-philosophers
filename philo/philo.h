/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:46:09 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/21 19:56:43 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				meals;
	int				eating;
	u_int64_t		life_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}		t_philo;

typedef struct s_data
{
	pthread_t		*td;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				dead;
	int				finished;
	u_int64_t		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	t_philo			*philo;
}		t_data;

int			check_args(const char *str);
int			storing(t_data *data);
int			init_table(t_data *data);
int			init(int ac, char **av, t_data *data);
int			init_thread(t_data *data);
void		*routine(void *arg);
void		*check_meals(void *arg);
void		*check_death(void *arg);
void		life_cycle(t_philo *philo);
void		message(char *str, t_philo *philo);
u_int64_t	get_time(void);
int			error(char *str, t_data *data, int flag);
void		clear_data(t_data *data);
void		ft_exit(t_data *data);
int			ft_usleep(u_int64_t time);

#endif