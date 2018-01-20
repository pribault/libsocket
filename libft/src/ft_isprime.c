/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:35:04 by pribault          #+#    #+#             */
/*   Updated: 2018/01/20 12:35:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isprime(int n)
{
	int		midd;
	int		i;

	if (n <= 1)
		return (0);
	i = 2;
	midd = n / 2;
	while (i < midd)
		if (n % i++ == 0)
			return (0);
	return (1);
}
