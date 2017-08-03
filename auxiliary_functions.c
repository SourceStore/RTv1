/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:41:45 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 18:21:51 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			exit_win(void *param)
{
	param = NULL;
	exit(0);
	return (0);
}

int			close_win(int keykode)
{
	if (keykode == 53 || keykode == 65307)
		exit(0);
	return (0);
}

void		ft_swap(double *param1, double *param2)
{
	double	buffer;

	buffer = *param1;
	*param1 = *param2;
	*param2 = buffer;
}

int			len_matrix(char **str)
{
	int		len;

	if (!str)
		return (0);
	len = -1;
	while (str[++len])
		;
	return (len);
}

double		len_vect(t_vec vec)
{
	return (sqrt(SQR(vec.x) + SQR(vec.y) + SQR(vec.z)));
}
