/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_get_timeout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:25:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:50:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

t_timeval	*socket_get_timeout(t_socket *socket)
{
	static t_timeval	copy;

	ft_memcpy(&copy, &socket->timeout, sizeof(t_timeval));
	return (&copy);
}
