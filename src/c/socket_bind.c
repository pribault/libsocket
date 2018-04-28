/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_bind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:13:41 by pribault          #+#    #+#             */
/*   Updated: 2018/04/28 13:18:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Copyright © 2018 <pribault@student.42.fr>
**
**	Permission is hereby granted, free of charge, to any person obtaining a
**	copy of this software and associated documentation files (the “Software”),
**	to deal in the Software without restriction, including without limitation
**	the rights to use, copy, modify, merge, publish, distribute, sublicense,
**	and/or sell copies of the Software, and to permit persons to whom the
**	Software is furnished to do so, subject to the following conditions:
**
**	The above copyright notice and this permission notice shall be included in
**	all copies or substantial portions of the Software.
**
**	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
**	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
**	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
**	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
**	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
**	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
**	OTHER DEALINGS IN THE SOFTWARE.
*/

#define LIBSOCKET_INTERNAL

#include "libsocket.h"

static int	socket_bind_and_listen(t_socket *msocket)
{
	struct sockaddr_in6	addr;
	int					n;

	addr.sin6_family = msocket->domain;
	addr.sin6_port = htons(msocket->port);
	addr.sin6_addr = in6addr_any;
	n = 1;
	if ((msocket->sockfd = socket(msocket->domain, msocket->protocol, 0))
		< 0 || setsockopt(msocket->sockfd, SOL_SOCKET, SO_REUSEADDR, &n,
		sizeof(int)) < 0 ||
		bind(msocket->sockfd, (void*)&addr, (msocket->domain == IPV4) ?
		sizeof(struct sockaddr) : sizeof(struct sockaddr_in6)) < 0)
		return (0);
	if (msocket->protocol == TCP &&
		listen(msocket->sockfd, msocket->queue_max) < 0)
		return (0);
	if (msocket->socket_bind)
		msocket->socket_bind(msocket);
	return (1);
}

int			socket_bind(t_socket *socket, t_method method, char *port)
{
	if ((socket->opt & SERVER_RUNNING))
		return (0);
	socket->opt |= SERVER_RUNNING;
	socket->port = ft_atou(port);
	socket->protocol = method.protocol;
	socket->domain = method.domain;
	return (socket_bind_and_listen(socket));
}
