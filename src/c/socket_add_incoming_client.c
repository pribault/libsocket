/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_add_incoming_client.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:57:49 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 14:58:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_add_incoming_client(t_socket *socket, int *n_evts)
{
	struct hostent	*host;
	t_client		client;

	ft_bzero(&client, sizeof(t_client));
	client.addr.len = sizeof(struct sockaddr);
	if ((*n_evts) < 1 ||
		(client.fd = accept(socket->sockfd, (void*)&client.addr,
		&client.addr.len)) < 0)
		return ;
	host = gethostbyaddr(&client.addr.addr, client.addr.len, socket->domain);
	client.addr.str = ft_strdup(host->h_name);
	client.write_type = WRITE_BY_ADDR;
	(*n_evts)--;
	ft_vector_add(&socket->clients, &client);
	if (socket->client_add)
		socket->client_add(socket, ft_vector_get(&socket->clients,
		socket->clients.n - 1));
}
