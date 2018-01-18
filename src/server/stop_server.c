/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:20:08 by pribault          #+#    #+#             */
/*   Updated: 2018/01/18 21:45:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		stop_server(t_server *server)
{
	t_server_client	*client;
	t_towrite		*towrite;
	size_t			i;

	if (!server)
		return (0);
	server->opt &= ~SERVER_RUNNING;
	i = (size_t)-1;
	while (++i < server->write_queue->n)
		if ((towrite = ft_vector_get(server->write_queue, i)))
			free(towrite->data);
	ft_vector_resize(server->write_queue, 0);
	i = (size_t)-1;
	while (++i < server->clients->n)
		if ((client = ft_vector_get(server->clients, i)))
			close(client->fd);
	ft_vector_resize(server->clients, 0);
	close(server->sockfd);
	return (1);
}
