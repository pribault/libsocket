/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:32:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:31:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LIBSOCKET_INTERNAL

#include "libsocket.h"

static void	socket_trash_callback(t_socket *socket, t_towrite *towrite)
{
	if (socket->msg_trash)
		socket->msg_trash(socket, &towrite->client, &towrite->data);
}

t_socket	*socket_new(void)
{
	t_socket	*socket;

	if (!(socket = (t_socket*)malloc(sizeof(t_socket))))
		return (NULL);
	ft_bzero(socket, sizeof(t_socket));
	ft_vector_init(&socket->clients, ALLOC_MALLOC, sizeof(t_client));
	ft_circ_buffer_init(&socket->write_queue, ALLOC_MALLOC,
	sizeof(t_towrite), CIRCULAR_BUFFER_SIZE);
	ft_circ_buffer_set_trash_callback(&socket->write_queue,
	(void*)&socket_trash_callback, socket);
	socket->queue_max = DEFAULT_QUEUE_MAX;
	socket->timeout = TIMEVAL(DEFAULT_TIMEOUT_S, DEFAULT_TIMEOUT_US);
	socket->read_size = DEFAULT_READ_BUFFER_SIZE;
	socket->opt = 0;
	return (socket);
}
