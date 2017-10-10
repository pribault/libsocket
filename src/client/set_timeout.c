/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_timeout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 17:18:08 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 20:52:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		set_client_timeout(t_client *client, size_t seconds)
{
	if (!client)
		return (0);
	pthread_mutex_lock(&client->autocleaner_mutex);
	client->timeout = seconds;
	pthread_mutex_unlock(&client->autocleaner_mutex);
	return (1);
}
