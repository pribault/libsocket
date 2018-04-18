/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_set_timeout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:25:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:49:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_set_timeout(t_socket *socket, t_timeval *timeout)
{
	ft_memcpy(&socket->timeout, timeout, sizeof(t_timeval));
}
