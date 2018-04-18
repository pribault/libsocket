/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_poll_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:54:53 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 11:03:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LIBSOCKET_INTERNAL

#include "libsocket.h"

static void	socket_add_clients_to_set(fd_set *set, fd_set *err_set,
			t_vector *clients, int *fd_max)
{
	t_client	*client;
	size_t		i;

	i = (size_t)clients->n;
	while (--i != (size_t)-1)
	{
		if ((client = ft_vector_get(clients, i)))
		{
			if (!FD_ISSET(client->fd, set) ||
				!FD_ISSET(client->fd, err_set))
			{
				if (client->fd > *fd_max)
					*fd_max = client->fd;
				FD_SET(client->fd, set);
				FD_SET(client->fd, err_set);
			}
		}
	}
}

static void	socket_add_write_request_to_set(fd_set *set, t_circ_buffer *queue,
			int *fd_max)
{
	t_towrite	*towrite;
	size_t		i;

	i = (size_t)-1;
	while ((towrite = ft_circ_buffer_get(queue, ++i)))
	{
		if (towrite->client.fd > *fd_max)
			*fd_max = towrite->client.fd;
		FD_SET(towrite->client.fd, set);
	}
}

static void	set_sets(t_socket *socket, fd_set *set, int *fd_max)
{
	FD_ZERO(&set[0]);
	FD_ZERO(&set[1]);
	FD_ZERO(&set[2]);
	FD_SET(socket->sockfd, &set[0]);
	FD_SET(socket->sockfd, &set[2]);
	*fd_max = socket->sockfd;
	socket_add_clients_to_set(&set[0], &set[2], &socket->clients, fd_max);
	socket_add_write_request_to_set(&set[1], &socket->write_queue, fd_max);
}

void		socket_poll_events(t_socket *socket)
{
	struct timeval	time;
	fd_set			set[3];
	int				fd_max;
	int				ret;

	fd_max = -42;
	set_sets(socket, (fd_set*)&set, &fd_max);
	time = socket->timeout;
	if ((ret = select(fd_max + 1, &set[0], &set[1], &set[2],
		&time)) <= 0)
		return ;
	if (FD_ISSET(socket->sockfd, &set[0]))
	{
		if (socket->protocol == TCP)
			socket_add_incoming_client(socket, &ret);
		else if (socket->protocol == UDP)
			socket_get_incoming_message(socket, &ret);
	}
	if (FD_ISSET(socket->sockfd, &set[2]) && socket->socket_excpt)
		socket->socket_excpt(socket);
	socket_manage_incoming_messages(socket, &set[0], &set[2], &ret);
	socket_manage_write_requests(socket, &set[1], &ret);
}
