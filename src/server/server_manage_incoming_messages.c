/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_incoming_messages.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:18:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 21:55:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_complete_msg(t_server *server, t_client *client,
			void *buffer, size_t size)
{
	static t_msg	msg;

	if (!server || !client || !buffer || !size)
		return ;
	if (client->size + size < client->expected)
	{
		if (!(client->data = realloc(client->data, client->size + size)))
			return ;
		ft_memcpy(client->data + client->size, buffer, size);
		client->size += size;
	}
	else
	{
		if (!(client->data = realloc(client->data, client->expected)))
			return ;
		ft_memcpy(client->data + client->size, buffer,
		client->expected - client->size);
		msg.ptr = client->data;
		msg.size = client->expected;
		if (server->msg_recv)
			server->msg_recv(server, client, &msg);
		ft_memdel((void**)&client->data);
		client->size = 0;
		client->expected = 0;
	}
}

static void	server_get_msg(t_server *server, t_client *client,
			void *buffer, size_t size)
{
	static t_msg	msg;

	if (!server || !client || !buffer || !size)
		return ;
	if (*(size_t*)buffer + sizeof(size_t) <= size)
	{
		msg.ptr = buffer + sizeof(size_t);
		msg.size = *(size_t*)buffer;
		if (server->msg_recv)
			server->msg_recv(server, client, &msg);
		server_get_msg(server, client, msg.ptr + msg.size,
		size - (msg.size + sizeof(size_t)));
	}
	else
	{
		if (!(client->data = malloc(size - sizeof(size_t))))
			return ;
		client->expected = *(size_t*)buffer;
		client->size = size - sizeof(size_t);
	}
}

static void	server_get_client_message(t_server *server, t_client *client)
{
	static char	buffer[READ_BUFFER_SIZE];
	int			ret;

	if (!server || !client)
		return ;
	if ((ret = read(client->fd, &buffer, READ_BUFFER_SIZE)) < 0)
		return ;
	if (!ret)
		server_remove_client(server, client);
	if (client->data)
		server_complete_msg(server, client, &buffer, ret);
	else if ((size_t)ret >= sizeof(size_t))
		server_get_msg(server, client, &buffer, ret);
}

void		server_manage_incoming_messages(t_server *server, fd_set *set,
			int *n_evts)
{
	t_vector	*vector;
	t_client	*client;
	size_t		i;

	if (!server || !set || !n_evts || (*n_evts) < 1 ||
		!(vector = server->clients))
		return ;
	i = vector->n;
	while (--i != (size_t)-1 && (*n_evts))
	{
		if ((client = ft_vector_get(vector, i)) &&
			FD_ISSET(client->fd, set))
		{
			server_get_client_message(server, client);
			(*n_evts)--;
		}
	}
}
