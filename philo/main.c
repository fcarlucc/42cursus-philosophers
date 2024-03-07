/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:46:14 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/01/09 17:11:41 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (storing(&data) == 1)
		{
			if (init_table(&data) == 1)
			{
				if (init_thread(&data) == 1)
				{
					return (0);
				}
			}
		}
	}
	return (1);
}
