/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:18:27 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/19 13:40:34 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_manager(int error)
{
	if (error == FEW_ARGS)
	{
		printf("Not enough arguments. 4 Needed to work properly.\n");
		return (-1);
	}
	if (error == TOO_ARGS)
	{
		printf("Too much arguments. 4 Needed to work properly.\n");
		return (-1);
	}
	if (error == BAD_ARGS)
		return (printf("Incorrect values.\n"), -1);
	if (error == MALLOC_ERROR)
	{
		printf("An error occured with a malloc call.\n");
		return (-1);
	}
	return (0);
}
