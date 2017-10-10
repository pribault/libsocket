/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_autocleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 17:18:18 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:00:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		stop_client_autocleaner(t_client *client)
{
	if (!client || !(client->running & AUTOCLEANER))
		return (0);
	pthread_mutex_lock(&client->autocleaner_mutex);
	pthread_cancel(client->autocleaner);
	pthread_mutex_unlock(&client->autocleaner_mutex);
	client->running -= AUTOCLEANER;
	return (1);
}
