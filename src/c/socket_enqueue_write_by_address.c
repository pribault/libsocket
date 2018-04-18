/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_enqueue_write_by_address.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:34:07 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 14:39:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_enqueue_write_by_address(t_socket *socket,
		struct sockaddr_storage *address, t_msg *msg)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	ft_memcpy(&client.addr, address, sizeof(struct sockaddr_storage));
	client.write_type = WRITE_BY_ADDRESS;
	socket_enqueue_write(socket, &client, msg);
}
