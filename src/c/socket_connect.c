/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:26:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:00:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static int	iter_on_addresses(t_socket *socket, t_client *client,
			struct addrinfo *result)
{
	struct addrinfo	*addr;

	addr = result;
	while (addr)
	{
		if (connect(client->fd, addr->ai_addr, addr->ai_addrlen) >= 0)
		{
			ft_memcpy(&client->addr, addr->ai_addr, addr->ai_addrlen);
			client->addr.len = addr->ai_addrlen;
			client->write_type = WRITE_BY_ADDR;
			ft_vector_add(&socket->clients, client);
			if (socket->client_add)
				socket->client_add(socket, ft_vector_get(&socket->clients,
				socket->clients.n - 1));
			freeaddrinfo(result);
			return (1);
		}
		addr = addr->ai_next;
	}
	freeaddrinfo(result);
	return (0);
}

int			socket_connect(t_socket *msocket, t_method method, char *address,
			char *port)
{
	t_client		client;
	struct addrinfo	hints;
	struct addrinfo	*result;

	ft_bzero(&hints, sizeof(struct addrinfo));
	ft_bzero(&client, sizeof(t_client));
	hints.ai_family = method.domain;
	hints.ai_socktype = method.protocol;
	result = NULL;
	if (getaddrinfo(address, port, &hints, &result) != 0 ||
		(client.fd = socket(method.domain, method.protocol, 0)) < 0)
	{
		if (result)
			freeaddrinfo(result);
		return (0);
	}
	return (iter_on_addresses(msocket, &client, result));
}
