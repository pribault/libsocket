/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:06:13 by pribault          #+#    #+#             */
/*   Updated: 2018/01/18 23:04:18 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		server_start_tcp(t_server *server)
{
	if (listen(server->sockfd, server->queue_max) < 0)
		return (0);
	server->opt |= SERVER_RUNNING;
	return (1);
}

int		server_start_udp(t_server *server)
{
	server->opt |= SERVER_RUNNING;
	return (1);
}

int		server_start(t_server *server)
{
	struct sockaddr_in	addr;
	int					n;

	if (!server)
		return (0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(server->port);
	addr.sin_addr.s_addr = INADDR_ANY;
	n = 1;
	if ((server->sockfd = socket(AF_INET, server->protocol, 0)) < 0 ||
		setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &n,
		sizeof(int)) < 0 ||
		bind(server->sockfd, (void*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (0);
	if (server->protocol == TCP)
		return (server_start_tcp(server));
	else if (server->protocol == UDP)
		return (server_start_udp(server));
	else
		return (0);
}
