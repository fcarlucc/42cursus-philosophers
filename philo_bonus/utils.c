/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:17:33 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/21 20:02:25 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_exit(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
}

int	check_args(const char *str)
{
	long	n;
	int		s;
	int		i;

	n = 0;
	s = 1;
	i = 0;
	if (str[i] == '-')
		n *= -1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (error(NULL, NULL, 1));
		n = n * 10;
		n = n + str[i] - '0';
		i++;
	}
	if ((n * s) > 2147483647 || (n * s) < -2147483648)
		return (error(NULL, NULL, 1));
	n = (int)n;
	return (n * s);
}
