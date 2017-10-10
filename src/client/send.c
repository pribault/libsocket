/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 14:07:38 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 14:49:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

size_t	send_client(t_client *client, void *data, size_t size)
{
	t_pack	pack;
	size_t	total;
	size_t	tmp;

	if (!client || client->sockfd == -1)
		return (0);
	total = 0;
	while (total < size)
	{
		pack.size = (size - total >= PACKAGE_SIZE_MAX) ?
		PACKAGE_SIZE_MAX : (size - total);
		memcpy(&pack.data, data + total, pack.size);
		if ((tmp = sendto(client->sockfd, &pack.data, pack.size, 0,
		client->addr->ai_addr, client->addr->ai_addrlen)) == (size_t)-1)
			return (0);
		total += tmp;
	}
	return (total);
}
