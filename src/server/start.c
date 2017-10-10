/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:40:04 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:01:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static t_id	*search_client(t_vector *clients, t_id *id)
{
	t_id	*client;
	size_t	i;

	i = 0;
	while (i < clients->n)
	{
		client = (t_id*)ft_vector_get(clients, i++);
		if (!ft_memcmp(id, client, sizeof(t_sockaddr) + sizeof(socklen_t)))
			return (client);
	}
	return (NULL);
}

static void	loop(t_server *server)
{
	static t_pack	pack;
	t_id			*client;

	while (1)
	{
		pack.id.addr_len = sizeof(t_sockaddr);
		if ((pack.size = recvfrom(server->sockfd, &pack.data, PACKAGE_SIZE_MAX,
		0, &pack.id.addr, &pack.id.addr_len)) != (size_t)-1)
		{
			pthread_mutex_lock(&server->receiver_mutex);
			ft_vector_add(server->waiting, &pack);
			pthread_mutex_unlock(&server->receiver_mutex);
			pthread_mutex_lock(&server->autocleaner_mutex);
			if ((client = search_client(server->clients, &pack.id)))
				client->last = time(NULL);
			else
			{
				pack.id.last = time(NULL);
				ft_vector_add(server->clients, &pack.id);
			}
			pthread_mutex_unlock(&server->autocleaner_mutex);
		}
	}
}

int			start_server(t_server *server)
{
	if (!server || (server->running & RECEIVER) ||
	pthread_create(&server->receiver, NULL, (void*)&loop, server))
		return (0);
	server->running += RECEIVER;
	return (1);
}
