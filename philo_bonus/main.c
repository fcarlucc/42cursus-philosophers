/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:00:51 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/06/21 19:59:32 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("ARGS NEEDED 5 OR 6");
		return (1);
	}
	if (init(ac, av, &data) == 1)
	{
		if (init_table(&data) == 1)
		{
			init_processes(&data);
			return (0);
		}
	}
	return (1);
}
