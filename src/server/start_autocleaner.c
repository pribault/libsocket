/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_autocleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 11:33:06 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 20:56:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static void	loop(t_server *server)
{
	time_t	now;
	size_t	refresh;
	size_t	i;
	t_id	*client;

	while (1)
	{
		now = time(NULL);
		pthread_mutex_lock(&server->autocleaner_mutex);
		i = 0;
		while (i < server->clients->n)
		{
			client = (t_id*)ft_vector_get(server->clients, i++);
			if ((size_t)(now - client->last) > server->timeout)
			{
				ft_printf("BOUM get out of here %lu !\n", i - 1);
				ft_vector_del_one(server->clients, i - 1);
			}
		}
		refresh = server->refresh;
		pthread_mutex_unlock(&server->autocleaner_mutex);
		usleep(refresh);
	}
}

int			start_server_autocleaner(t_server *server)
{
	if (!server || (server->running & AUTOCLEANER) ||
	pthread_create(&server->autocleaner, NULL, (void*)&loop, server))
		return (0);
	server->running += AUTOCLEANER;
	return (1);
}
