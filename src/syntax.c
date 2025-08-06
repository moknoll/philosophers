/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritz <moritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:01:28 by mknoll            #+#    #+#             */
/*   Updated: 2025/07/28 16:01:53 by moritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isvalid(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_syntax(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isvalid(argv[i][j]))
			{
				printf("Input is not valid: %s\n", argv[i]);
				return (0);
			}
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) > 200)
	{
		printf("No more than 200 philosophers\n");
		return (0);
	}
	return (1);
}

int	check_args(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("Input not correct\n");
		return (0);
	}
	if (!check_syntax(argc, argv))
		return (0);
	return (1);
}
