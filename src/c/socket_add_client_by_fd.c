/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_add_client_by_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:41:01 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 14:41:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_add_client_by_fd(t_socket *socket, int fd)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.fd = fd;
	client.write_type = WRITE_BY_FD;
	ft_vector_add(&socket->clients, &client);
	if (socket->client_add)
		socket->client_add(socket, ft_vector_get(&socket->clients,
		socket->clients.n - 1));
}
