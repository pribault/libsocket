/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 21:23:23 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:08:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"
#include "libft.h"

void	client_add(t_server *server, t_client *client)
{
	t_msg	msg;

	(void)server;
	msg.ptr = ft_joinf("client [%s] added\n", server_get_client_address(client));
	msg.size = ft_strlen(msg.ptr);
	server_enqueue_write_by_fd(server, 1, &msg);
}

void	client_del(t_server *server, t_client *client)
{
	t_msg	msg;

	(void)server;
	msg.ptr = ft_joinf("client [%s] deleted\n", server_get_client_address(client));
	msg.size = ft_strlen(msg.ptr);
	server_enqueue_write_by_fd(server, 1, &msg);
}

void	msg_recv(t_server *server, t_client *client, t_msg *msg)
{
	t_msg	new_msg;

	(void)server;
	(void)msg;
	new_msg.ptr = ft_joinf("message received from [%s]:\n",
	server_get_client_address(client));
	new_msg.size = ft_strlen(new_msg.ptr);
	server_enqueue_write_by_fd(server, 1, &new_msg);
}

void	msg_send(t_server *server, t_client *client, t_msg *msg)
{
	t_msg	new_msg;

	(void)server;
	(void)msg;
	if (server_get_client_fd(client) <= 1)
		return ;
	new_msg.ptr = ft_joinf("message sended to [%s]:\n", server_get_client_address(client));
	new_msg.size = ft_strlen(new_msg.ptr);
	server_enqueue_write_by_fd(server, 1, &new_msg);
}

int	main(int argc, char **argv)
{
	t_server	*server;

	if (argc != 2)
		return (1);
	server = server_new();
	server_set_queue_max(server, 1);
	server_set_clients_max(server, 10);
	server_start(server, TCP);
	server_bind(server, argv[1]);
	server_set_callback(server, CLIENT_ADD_CB, &client_add);
	server_set_callback(server, CLIENT_DEL_CB, &client_del);
	server_set_callback(server, MSG_RECV_CB, &msg_recv);
	server_set_callback(server, MSG_SEND_CB, &msg_send);
	server_add_client_by_fd(server, 0);
	while (1)
	{
		server_poll_events(server);
	}
	return (0);
}
