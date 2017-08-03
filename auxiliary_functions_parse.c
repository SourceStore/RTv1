/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions_parse.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 18:21:39 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:49:53 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	del_buf(char **str)
{
	int	size;
	int	i;

	i = -1;
	size = 0;
	while (str[++i])
		size++;
	i = -1;
	while (++i < size)
		ft_strdel(&str[i]);
}

int		incor_char(char **arg)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (!ft_isdigit(arg[j][i]) && i != 0)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int		check_num(char **str)
{
	if (!incor_char(str))
		return (0);
	return (1);
}

void	len_str(char **str)
{
	int	i;
	int	len;

	i = -1;
	while (str[++i])
	{
		len = -1;
		while (str[i][++len])
			;
		if (len > 6)
			exit(write(1, "Invalid data\n", 14));
	}
}
