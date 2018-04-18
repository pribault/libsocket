/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_enqueue_write.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:53:11 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:33:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LIBSOCKET_INTERNAL

#include "libsocket.h"

void	socket_enqueue_write(t_socket *socket, t_client *client,
		t_msg *msg)
{
	t_towrite	towrite;

	ft_memcpy(&towrite.client, client, sizeof(t_client));
	ft_memcpy(&towrite.data, msg, sizeof(t_msg));
	ft_circ_buffer_enqueue(&socket->write_queue, &towrite);
	if (ft_circ_buffer_get_size(&socket->write_queue) >=
		CIRCULAR_BUFFER_SIZE - 2 &&
		socket->buffer_full)
		socket->buffer_full(socket);
}
