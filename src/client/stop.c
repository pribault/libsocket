/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:52:15 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:20:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		stop_client(t_client *client)
{
	if (!client || !client->running)
		return (0);
	stop_client_autocleaner(client);
	pthread_mutex_lock(&client->receiver_mutex);
	pthread_mutex_lock(&client->autocleaner_mutex);
	pthread_cancel(client->receiver);
	pthread_mutex_unlock(&client->autocleaner_mutex);
	pthread_mutex_unlock(&client->receiver_mutex);
	client->running = 0;
	return (1);
}
