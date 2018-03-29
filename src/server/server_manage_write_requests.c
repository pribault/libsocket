/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_write_requests.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:18:05 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 18:17:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_manage_write_requests_tcp(t_server *server, fd_set *set,
			int *n_evts)
{
	t_towrite		*towrite;
	t_circ_buffer	*buffer;
	uint64_t		size;
	uint64_t		i;

	if ((*n_evts) < 1)
		return ;
	buffer = &server->write_queue;
	i = (uint64_t)-1;
	size = ft_circ_buffer_get_size(buffer);
	while (++i < size &&
		(towrite = ft_circ_buffer_dequeue(buffer)))
		if (FD_ISSET(towrite->client.fd, set))
		{
			FD_CLR(towrite->client.fd, set);
			if (write(towrite->client.fd, towrite->data.ptr,
				towrite->data.size) < 0)
				return (ft_circ_buffer_enqueue(buffer, towrite));
			if (server->msg_send)
				server->msg_send(server, &towrite->client, &towrite->data);
			(*n_evts)--;
		}
		else
			ft_circ_buffer_enqueue(buffer, towrite);
}

static int	server_try_write_udp(t_circ_buffer *buffer, t_towrite *towrite)
{
	if (sendto(towrite->client.fd, towrite->data.ptr,
		towrite->data.size, 0, &towrite->client.addr,
		towrite->client.addr_len) < 0 &&
		write(towrite->client.fd, towrite->data.ptr,
		towrite->data.size) < 0)
	{
		ft_circ_buffer_enqueue(buffer, towrite);
		return (0);
	}
	return (1);
}

static void	server_manage_write_requests_udp(t_server *server, fd_set *set,
			int *n_evts)
{
	t_towrite		*towrite;
	t_circ_buffer	*buffer;
	uint64_t		size;
	uint64_t		i;

	if ((*n_evts) < 1)
		return ;
	buffer = &server->write_queue;
	i = (uint64_t)-1;
	size = ft_circ_buffer_get_size(buffer);
	while (++i < size &&
		(towrite = ft_circ_buffer_dequeue(buffer)))
		if (FD_ISSET(towrite->client.fd, set))
		{
			FD_CLR(towrite->client.fd, set);
			if (!server_try_write_udp(buffer, towrite))
				return ;
			if (server->msg_send)
				server->msg_send(server, &towrite->client, &towrite->data);
			(*n_evts)--;
		}
		else
			ft_circ_buffer_enqueue(buffer, towrite);
}

void		server_manage_write_requests(t_server *server, fd_set *set,
			int *n_evts)
{
	if (server->protocol == TCP)
		server_manage_write_requests_tcp(server, set, n_evts);
	else if (server->protocol == UDP)
		server_manage_write_requests_udp(server, set, n_evts);
}
