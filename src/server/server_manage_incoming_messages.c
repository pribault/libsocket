/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_incoming_messages.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:18:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 23:02:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_complete_msg(t_server *server, t_client *client,
			void *buffer, size_t size)
{
	static t_msg	msg;

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
		server_get_client_message(server, client, buffer + client->expected -
		client->size, size + client->size - client->expected);
	}
}

static void	server_get_msg(t_server *server, t_client *client,
			void *buffer, size_t size)
{
	static t_msg	msg;

	if (*(size_t*)buffer + sizeof(size_t) <= size)
	{
		msg.ptr = buffer + sizeof(size_t);
		msg.size = *(size_t*)buffer;
		if (server->msg_recv)
			server->msg_recv(server, client, &msg);
		server_get_client_message(server, client, msg.ptr + msg.size,
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

void		server_get_client_message(t_server *server, t_client *client,
			void *data, size_t size)
{
	if (!size)
		return ;
	if (client->data)
		server_complete_msg(server, client, data, size);
	else if ((size_t)size >= sizeof(size_t))
		server_get_msg(server, client, data, size);
}

void		server_manage_incoming_messages(t_server *server, fd_set *set,
			int *n_evts)
{
	static char	buffer[READ_BUFFER_SIZE];
	t_vector	*vector;
	t_client	*client;
	int			ret;
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
			if ((ret = read(client->fd, &buffer, READ_BUFFER_SIZE)) > 0)
				server_get_client_message(server, client, (void*)&buffer, ret);
			else if (!ret)
				server_remove_client(server, client);
			ft_vector_del_one(vector, i);
			(*n_evts)--;
		}
	}
}
