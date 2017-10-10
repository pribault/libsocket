/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:39:56 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:22:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static void	loop(t_client *client)
{
	static t_pack	pack;

	while (1)
	{
		pack.size = recvfrom(client->sockfd, &pack.data, PACKAGE_SIZE_MAX, 0,
		&pack.id.addr, &pack.id.addr_len);
		pthread_mutex_lock(&client->receiver_mutex);
		time(&client->last);
		ft_vector_add(client->waiting, &pack);
		pthread_mutex_unlock(&client->receiver_mutex);
	}
}

int			start_client(t_client *client)
{
	if (!client || (client->running & RECEIVER) ||
	(client->running & AUTOCLEANER) ||
	pthread_create(&client->receiver, NULL, (void*)&loop, client))
		return (0);
	client->running = 1;
	return (1);
}
