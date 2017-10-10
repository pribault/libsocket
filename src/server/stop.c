/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:52:22 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:26:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		stop_server(t_server *server)
{
	if (!server || !(server->running & RECEIVER))
		return (0);
	pthread_mutex_lock(&server->receiver_mutex);
	pthread_mutex_lock(&server->autocleaner_mutex);
	pthread_cancel(server->receiver);
	pthread_mutex_unlock(&server->autocleaner_mutex);
	pthread_mutex_unlock(&server->receiver_mutex);
	server->running -= RECEIVER;
	return (1);
}
