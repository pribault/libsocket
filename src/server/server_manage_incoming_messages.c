/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_incoming_messages.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:18:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/20 09:43:03 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_get_client_message(t_server *server, t_client *client,
			void *data, size_t size)
{
	static t_msg	msg;

	if (server->msg_recv)
	{
		msg.ptr = data;
		msg.size = size;
		server->msg_recv(server, client, &msg);
	}
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
			(*n_evts)--;
		}
	}
}
