/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 21:23:23 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 16:31:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"
#include "libft.h"

static t_client	*last = NULL;

void	client_add(t_socket *socket, t_client *client)
{
	ft_printf("client [%s] added\n", client_get_address(client)->str);
}

void	client_del(t_socket *socket, t_client *client)
{
	ft_printf("client [%s] deleted\n", client_get_address(client)->str);
	if (last == client)
		last = NULL;
}

void	msg_recv(t_socket *socket, t_client *client, t_msg *msg)
{
	if (client_get_fd(client) == 0)
	{
		if (last)
			socket_enqueue_write(socket, last, msg);
	}
	else
	{
		ft_printf("message of size %d received from [%s]\n",
			msg->size, client_get_address(client)->str);
		socket_enqueue_write_by_fd(socket, 1, msg);
		last = client;
	}
}

void	msg_send(t_socket *socket, t_client *client, t_msg *msg)
{
	if (client_get_fd(client) <= 1)
		return ;
	ft_printf("message of size %d sended to [%s]\n", msg->size,
		client_get_address(client)->str);
}

int	main(int argc, char **argv)
{
	t_socket	*socket;

	if (argc != 2)
		return (1);
	socket = socket_new();
	if (!socket_bind(socket, (t_method){TCP, IPV4}, argv[1]))
	{
		ft_printf("cannot bind to %s\n", argv[1]);
		return (1);
	}
	socket_set_callback(socket, SOCKET_CLIENT_ADD_CB, &client_add);
	socket_set_callback(socket, SOCKET_CLIENT_DEL_CB, &client_del);
	socket_set_callback(socket, SOCKET_MSG_RECV_CB, &msg_recv);
	socket_set_callback(socket, SOCKET_MSG_SEND_CB, &msg_send);
	socket_add_client_by_fd(socket, 0);
	while (1)
	{
		socket_poll_events(socket, ACCEPT_CONNECTIONS | ALLOW_READ | ALLOW_WRITE);
	}
	return (0);
}
