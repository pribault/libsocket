/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_refresh_rate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 17:18:05 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:20:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		set_client_refresh_rate(t_client *client, size_t microseconds)
{
	if (!client)
		return (0);
	pthread_mutex_lock(&client->autocleaner_mutex);
	client->refresh = microseconds;
	pthread_mutex_unlock(&client->autocleaner_mutex);
	return (1);
}
