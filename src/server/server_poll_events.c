/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_poll_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:31:22 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:48:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	set_sets(t_server *server, fd_set *set, int *fd_max)
{
	FD_ZERO(&set[0]);
	FD_ZERO(&set[1]);
	FD_ZERO(&set[2]);
	if (server->opt & SERVER_BIND)
	{
		FD_SET(server->sockfd, &set[0]);
		*fd_max = server->sockfd;
	}
	else
		*fd_max = 0;
	server_add_clients_to_set(&set[0], &set[2], server->clients, fd_max);
	server_add_write_request_to_set(&set[1], server->write_queue, fd_max);
}

int		server_poll_events(t_server *server)
{
	fd_set	set[3];
	int		fd_max;
	int		ret;

	if (!server || !(server->opt & SERVER_RUNNING))
		return (0);
	set_sets(server, (fd_set*)&set, &fd_max);
	if ((ret = select(fd_max + 1, &set[0], &set[1], &set[2],
		&server->timeout)) < 0)
		return (0);
	if (!ret)
		return (1);
	if (FD_ISSET(server->sockfd, &set[0]))
		server_add_incoming_client(server, &ret);
	server_manage_incoming_messages(server, &set[0], &set[2], &ret);
	server_manage_write_requests(server, &set[1], &ret);
	return (1);
}
