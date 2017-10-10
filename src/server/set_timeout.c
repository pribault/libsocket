/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_timeout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 14:09:06 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:17:03 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		set_server_timeout(t_server *server, size_t seconds)
{
	if (!server)
		return (0);
	pthread_mutex_lock(&server->autocleaner_mutex);
	server->timeout = seconds;
	pthread_mutex_unlock(&server->autocleaner_mutex);
	return (1);
}
