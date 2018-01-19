/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:56:42 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 09:01:01 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server	*server_new(void)
{
	t_server	*server;

	if (!(server = (t_server*)malloc(sizeof(t_server))) ||
		!(server->clients = ft_vector_new(sizeof(t_client), 0)) ||
		!(server->write_queue = ft_vector_new(sizeof(t_towrite), 0)))
	{
		if (server && server->clients)
			ft_vector_del(&server->clients);
		if (server)
			free(server);
		return (NULL);
	}
	ft_bzero(server, sizeof(t_server));
	server->queue_max = SERVER_DEFAULT_QUEUE_MAX;
	server->timeout = (struct timeval){SERVER_DEFAULT_TIMEOUT_S,
	SERVER_DEFAULT_TIMEOUT_US};
	server->opt = 0;
	return (server);
}
