/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_set_read_buffer_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:25:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:34:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_set_read_buffer_size(t_socket *socket, uint64_t read_size)
{
	socket->read_size = read_size;
}
