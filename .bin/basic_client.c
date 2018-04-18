/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:58:24 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 16:32:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"
#include "libft.h"

static t_client *server = NULL;

void	connected(t_socket *socket, t_client *client)
{
	if (client_get_fd(client) > 2)
	{
		server = client;
		ft_printf("connected\n");
	}
}

void	disconnected(t_socket *socket, t_client *client)
{
	if (client_get_fd(client) > 2)
	{
		server = NULL;
		ft_printf("disconnected\n");
	}
}

void	msg_recv(t_socket *socket, t_client *client, t_msg *msg)
{
	ft_printf("message of size %d received\n", msg->size);
	if (client_get_fd(client) == 0 && server)
		socket_enqueue_write(socket, server, msg);
	else
		socket_enqueue_write_by_fd(socket, 1, msg);
}

void	msg_send(t_socket *socket, t_client *client, t_msg *msg)
{
	if (client_get_fd(client) <= 2)
		return ;
	ft_printf("message of size %d sended\n", msg->size);
}

int		main(int argc, char **argv)
{
	t_socket	*socket;

	if (argc != 3)
		return (1);
	socket = socket_new();
	socket_set_callback(socket, SOCKET_CLIENT_ADD_CB, &connected);
	socket_set_callback(socket, SOCKET_CLIENT_DEL_CB, &disconnected);
	socket_set_callback(socket, SOCKET_MSG_RECV_CB, &msg_recv);
	socket_set_callback(socket, SOCKET_MSG_SEND_CB, &msg_send);
	socket_add_client_by_fd(socket, 0);
	if (!socket_connect(socket, (t_method){TCP, IPV4}, argv[1], argv[2]))
		return (1);
	while (1)
	{
		socket_poll_events(socket, ALLOW_READ | ALLOW_WRITE);
	}
	return (0);
}
