/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_manage_incoming_messages.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:05:18 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 11:06:04 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static void	socket_get_client_message(t_socket *socket, t_client *client)
{
	char	buffer[READ_BUFFER_SIZE];
	int		ret;
	t_msg	msg;

	if ((ret = read(client->fd, &buffer, READ_BUFFER_SIZE)) > 0)
	{
		if (socket->msg_recv)
		{
			msg.ptr = &buffer;
			msg.size = ret;
			socket->msg_recv(socket, client, &msg);
		}
	}
	else if (!ret)
		socket_remove_client(socket, client);
}

void		socket_manage_incoming_messages(t_socket *socket, fd_set *set,
			fd_set *err_set, int *n_evts)
{
	t_vector	*vector;
	t_client	*client;
	size_t		i;

	if ((*n_evts) < 1)
		return ;
	vector = &socket->clients;
	i = vector->n;
	while (--i != (size_t)-1 && (*n_evts))
	{
		if ((client = ft_vector_get(vector, i)))
		{
			if (FD_ISSET(client->fd, err_set))
			{
				socket_remove_client(socket, client);
				(*n_evts)--;
			}
			else if (FD_ISSET(client->fd, set))
			{
				socket_get_client_message(socket, client);
				(*n_evts)--;
			}
		}
	}
}
