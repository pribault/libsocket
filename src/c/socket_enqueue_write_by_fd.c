/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_enqueue_write_by_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:31:03 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 14:33:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_enqueue_write_by_fd(t_socket *socket, int fd, t_msg *msg)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.fd = fd;
	client.write_type = WRITE_BY_FD;
	socket_enqueue_write(socket, &client, msg);
}
