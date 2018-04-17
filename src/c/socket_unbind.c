/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_unbind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:33:36 by pribault          #+#    #+#             */
/*   Updated: 2018/04/16 15:09:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void		socket_unbind(t_socket *socket)
{
	t_client	*client;
	t_towrite	*towrite;
	size_t		i;

	if (!(socket->opt & SERVER_RUNNING))
		return ;
	socket->opt &= ~SERVER_RUNNING;
	while ((towrite = ft_circ_buffer_dequeue(&socket->write_queue)))
		free(towrite->data.ptr);
	i = (size_t)-1;
	if (socket->protocol == TCP)
		while (++i < socket->clients.n)
			if ((client = ft_vector_get(&socket->clients, i)))
				close(client->fd);
	ft_vector_resize(&socket->clients, 0);
	close(socket->sockfd);
	if (socket->socket_unbind)
		socket->socket_unbind(socket);
}
