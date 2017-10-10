/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 14:07:43 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 16:36:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

size_t	send_server(t_server *server, t_id *id, void *data, size_t size)
{
	t_pack	pack;
	size_t	total;
	size_t	tmp;

	if (!server || server->sockfd == -1)
		return (0);
	total = 0;
	while (total < size)
	{
		pack.size = (size - total >= PACKAGE_SIZE_MAX) ?
		PACKAGE_SIZE_MAX : (size - total);
		memcpy(&pack.data, data + total, pack.size);
		if ((tmp = sendto(server->sockfd, &pack.data, pack.size, 0,
		&id->addr, id->addr_len)) == (size_t)-1)
			return (0);
		total += tmp;
	}
	return (total);
}
