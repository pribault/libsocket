/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_get_read_buffer_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:25:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:34:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

uint64_t	socket_get_read_buffer_size(t_socket *socket)
{
	return (socket->read_size);
}
