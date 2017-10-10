/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 12:12:36 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:27:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		destroy_client(t_client *client)
{
	if (!client || close(client->sockfd) == -1)
		return (0);
	stop_client(client);
	freeaddrinfo(client->addresses);
	ft_vector_del(&client->waiting);
	pthread_mutex_destroy(&client->receiver_mutex);
	pthread_mutex_destroy(&client->autocleaner_mutex);
	free(client);
	return (1);
}
