/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_autocleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 17:18:15 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:01:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static void	loop(t_client *client)
{
	time_t	now;
	size_t	refresh;

	while (1)
	{
		now = time(NULL);
		pthread_mutex_lock(&client->autocleaner_mutex);
		if ((size_t)(now - client->last) > client->timeout)
		{
			pthread_mutex_unlock(&client->autocleaner_mutex);
			stop_client(client);
			stop_client_autocleaner(client);
			return ;
		}
		refresh = client->refresh;
		pthread_mutex_unlock(&client->autocleaner_mutex);
		usleep(refresh);
	}
}

int			start_client_autocleaner(t_client *client)
{
	if (!client || (client->running & AUTOCLEANER) ||
	pthread_create(&client->autocleaner, NULL, (void*)&loop, client))
		return (0);
	client->running += AUTOCLEANER;
	return (1);
}
