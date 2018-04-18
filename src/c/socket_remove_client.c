/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_remove_client.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:20:23 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 11:21:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static void	socket_remove_client_by_fd(t_vector *vector,
			t_client *client)
{
	t_client	*tmp;
	size_t		i;

	i = vector->n;
	while (--i != (size_t)-1)
	{
		if ((tmp = ft_vector_get(vector, i)) &&
			tmp->fd == client->fd)
		{
			ft_vector_del_one(vector, i);
			return ;
		}
	}
}

void		socket_remove_client(t_socket *socket, t_client *client)
{
	t_vector	*vector;

	vector = &socket->clients;
	if (socket->client_del)
		socket->client_del(socket, client);
	close(client->fd);
	if ((void*)client >= vector->ptr &&
		(void*)client < vector->ptr + vector->size)
		ft_vector_del_one(vector, ((void*)client - vector->ptr) /
		vector->type);
	else
		socket_remove_client_by_fd(vector, client);
}
