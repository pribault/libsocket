/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_autocleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 11:33:10 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:17:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		stop_server_autocleaner(t_server *server)
{
	if (!server || !(server->running & AUTOCLEANER))
		return (0);
	pthread_mutex_lock(&server->autocleaner_mutex);
	pthread_cancel(server->autocleaner);
	pthread_mutex_unlock(&server->autocleaner_mutex);
	server->running -= AUTOCLEANER;
	return (1);
}
