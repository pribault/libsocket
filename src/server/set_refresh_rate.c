/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_refresh_rate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 11:37:09 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:16:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		set_server_refresh_rate(t_server *server, size_t microseconds)
{
	if (!server)
		return (0);
	pthread_mutex_lock(&server->autocleaner_mutex);
	server->refresh = microseconds;
	pthread_mutex_unlock(&server->autocleaner_mutex);
	return (1);
}
